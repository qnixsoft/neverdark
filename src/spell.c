#include "spell.h"

#include "mob.h"
#include "kill.h"

#include "params.h"
#include "props.h"
/* #include "speech.h" */
#include "externs.h"

element_t element_map[] = {
	[ELM_PHYSICAL] = {
		.color = "",
		.weakness = ELM_VAMP,
	},
	[ELM_FIRE] = {
		.color = ANSI_FG_RED,
		.weakness = ELM_ICE,
	},
	[ELM_ICE] = {
		.color = ANSI_FG_BLUE,
		.weakness = ELM_FIRE,
	},
	[ELM_AIR] = {
		.color = ANSI_FG_WHITE,
		.weakness = ELM_DARK,
	},
	[ELM_EARTH] = {
		.color = ANSI_FG_YELLOW,
		.weakness = ELM_AIR,
	},
	[ELM_SPIRIT] = {
		.color = ANSI_FG_MAGENTA,
		.weakness = ELM_VAMP,
	},
	[ELM_VAMP] = {
		.color = ANSI_BOLD ANSI_FG_BLACK,
		.weakness = ELM_SPIRIT,
	},
	[ELM_DARK] = {
		.color = ANSI_BOLD ANSI_FG_BLACK,
		.weakness = ELM_EARTH,
	},
};

spell_t spell_map[] = {
	[SPELL_HEAL] = {
		{"Heal", "", "" },
		ELM_PHYSICAL, 3, 1, 2, AF_HP,
	},

	[SPELL_FOCUS] = {
		{"Focus", "", "" },
		ELM_PHYSICAL, 15, 3, 1,
		AF_MDMG | AF_BUF,
	},

	[SPELL_FIRE_FOCUS] = {
		{"Fire Focus", "", "" },
		ELM_FIRE, 15, 3, 1,
		AF_MDMG | AF_BUF,
	},

	[SPELL_CUT] = {
		{"Cut", "", "" },
		ELM_PHYSICAL, 15, 1, 2,
		AF_NEG,
	},

	[SPELL_FIREBALL] = {
		{"Fireball", "", "" },
		ELM_FIRE, 3, 1, 2,
		AF_NEG,
	}, // 1/4 chance of burning

	[SPELL_WEAKEN] = {
		{"Weaken", "", "" },
		ELM_PHYSICAL, 15, 3, 1,
		AF_MDMG | AF_BUF | AF_NEG,
	},

	[SPELL_DISTRACT] = {
		{"Distract", "", "" },
		ELM_PHYSICAL, 15, 3, 1,
		AF_MDEF | AF_BUF | AF_NEG,
	},

	[SPELL_FREEZE] = {
		{"Freeze", "", "" },
		ELM_ICE, 10, 2, 4,
		AF_MOV | AF_NEG,
	},

	[SPELL_LAVA_SHIELD] = {
		{"Lava Shield", "", "" },
		ELM_FIRE, 15, 3, 1,
		AF_MDEF | AF_BUF,
	},

	[SPELL_WIND_VEIL] = {
		{"Wind Veil", "", "" },
		.flags = AF_DODGE,
	},

	[SPELL_STONE_SKIN] = {
		{"Stone Skin", "", "" },
		.flags = AF_DEF,
	},
};

struct wts buf_wts[] = {
	// HP
	{ "heal", "heals" },

	// - HP
	[16] =
	{ "bleed", "bleeds" },
	{ "burn", "burns" },

	// 32 MOV

	// - MOV
	[48] =
	{ "stunned", "stunned" },
	{ "", "" },
	{ "frozen", "frozen" },

	// MDMG
	[64] =
	{ "focus on attacking", "focuses on attacking" },
	{ "focus on fire", "focuses on fire" },

	// - MDMG
	[80] =
	{ "weaken", "weakens" },

	// MDEF
	[96] =
	{ "focus on defending", "focuses on defending" },
	{ "are protected by flames", "is protected by flames" },

	// - MDEF
	[112] =
	{ "are distracted", "is distracted" },

	// 128 DODGE

	// 144 - DDGE
};

enum element
element_next(ref_t ref, register unsigned char a)
{
	return a ? MOBI(ref)->debufs[__builtin_ffs(a) - 1]._sp->element
		: ELM_PHYSICAL;
}

static inline void
spell_init(
		spelli_t *sp, dbref player,
		unsigned intelligence,
		unsigned idx)
{
	spell_t *_sp = SPELL(idx);
	sp->_sp = _sp;
	sp->val = SPELL_DMG(player, _sp);
	sp->cost = SPELL_COST(sp->val, _sp->y, _sp->flags & AF_BUF);
}

void
spells_init(spelli_t sps[8], dbref player)
{
	char const *str = GETCURSPELLS(player);
	unsigned i = 0;
	unsigned intelligence = GETSTAT(player, INT);
	memset(sps, 0, sizeof(spelli_t) * 8);

	if (str && *str != '\0')
		for (; i < 8; i ++) {
			char *end;
			spell_init(&sps[i], player, intelligence,
			      strtoul(str, &end, 0));
			str = end;
			if (*str == '\0') {
				i++;
				break;
			}
			str++;
		}

	for (; i < 8; i++)
		spell_init(&sps[i], player, intelligence, 0);
}

void
debuf_end(dbref who, unsigned i)
{
	mobi_t *liv = MOBI(who);
	struct debuf *d = &liv->debufs[i];
	effect_t *e = EFFECT(who, DEBUF_TYPE(d->_sp));
	i = 1 << i;

	liv->debuf_mask ^= i;
	e->mask ^= i;
	e->value -= d->val;
}

static inline char const *
sp_color(spell_t *_sp)
{
	return DEBUF_TYPE(_sp) == AF_HP
		&& !(_sp->flags & AF_NEG)
		? ANSI_BOLD ANSI_FG_GREEN
		: ELEMENT(_sp->element)->color;
}

static inline struct wts *
debuf_wts(spell_t *_sp)
{
	register unsigned char mask = _sp->flags;
	register unsigned idx = (DEBUF_TYPE(_sp) << 1) + ((mask >> 4) & 1);
	idx = (idx << 4) + _sp->element;
	return &buf_wts[idx];
}

void
debuf_notify(dbref who, struct debuf *d, short val)
{
	char buf[BUFSIZ];
	register spell_t *_sp = d->_sp;
	char const *color = sp_color(_sp);
	struct wts *wts = debuf_wts(_sp);

	if (val)
		snprintf(buf, sizeof(buf), " (%s%d%s)", color, val, ANSI_RESET);
	else
		*buf = '\0';

	notify_wts(who, wts->a, wts->b, "%s", buf);
}

void
debufs_process(ref_t who)
{
	mobi_t *liv = MOBI(who);
	register unsigned mask, i, aux;
	short hpi = 0, dmg;
	struct debuf *d, *hd;

	for (mask = liv->debuf_mask, i = 0;
	     (aux = __builtin_ffs(mask));
	     i++, mask >>= aux)
	{
		i += aux - 1;
		d = &liv->debufs[i];
		d->duration--;
		if (d->duration == 0)
			debuf_end(liv->who, i);
		// wtf is this special code?
		else if (DEBUF_TYPE(d->_sp) == AF_HP) {
			dmg = kill_dmg(d->_sp->element, d->val,
				      MOBI_EV(liv, MDEF),
				      ELEMENT_NEXT(liv->who, MDEF));
			hd = d;

			hpi += dmg;
		}
	}

	if (hpi) {
		debuf_notify(liv->who, hd, hpi);
		cspell_heal(NOTHING, liv->who, hpi);
	}
}

void
debufs_end(dbref who)
{
	mobi_t *liv = MOBI(who);
	register unsigned mask, i, aux;

	for (mask = liv->debuf_mask, i = 0;
	     (aux = __builtin_ffs(mask));
	     i++, mask >>= aux)

		 debuf_end(who, i += aux - 1);
}

static inline int
debuf_start(dbref who, spelli_t *sp, short val)
{
	spell_t *_sp = sp->_sp;
	mobi_t *liv;
	struct debuf *d;
	int i;

	liv = MOBI(who);
	if (liv->debuf_mask) {
		i = __builtin_ffs(~liv->debuf_mask);
		if (!i)
			return -1;
		i--;
	} else
		i = 0;

	d = &liv->debufs[i];
	d->_sp = _sp;
	d->duration = DEBUF_DURATION(_sp->ra);
	d->val = DEBUF_DMG(val, d->duration);

	i = 1 << i;
	liv->debuf_mask |= i;

	effect_t *e = EFFECT(who, DEBUF_TYPE(_sp));
	e->mask |= i;
	e->value += d->val;

	debuf_notify(who, d, 0);

	return 0;
}

int
spell_cast(ref_t attacker, ref_t target, unsigned slot)
{
	mobi_t *att = MOBI(attacker);
	mobi_t *tar = att->target;
	spelli_t sp = att->spells[slot];
	spell_t *_sp = sp._sp;

	unsigned mana = att->mp;
	char a[BUFSIZ]; // FIXME way too big?
	char b[BUFSIZ];
	char c[BUFSIZ];
	struct wts wts = { a, b };

	char const *color = sp_color(_sp);

	if (mana < sp.cost)
		return -1;

	snprintf(a, sizeof(a), "%s%s"ANSI_RESET, color, _sp->o.name);
	memcpy(b, a, sizeof(a));

	mana -= sp.cost;
	att->mp = mana > 0 ? mana : 0;

	short val = kill_dmg(_sp->element, sp.val,
			MOBI_EV(tar, MDEF),
			ELEMENT_NEXT(tar->who, MDEF));

	if (_sp->flags & AF_NEG) {
		val = -val;
		if (kill_dodge(att, wts))
			return 0;
	} else
		target = attacker;

	snprintf(b, sizeof(b), "casts %s on", a);
	snprintf(c, sizeof(c), "cast %s on", a);
	wts.a = c;

	notify_attack(attacker, target, wts, 0, color, val);

	if (random() < (RAND_MAX >> _sp->y))
		debuf_start(target, &sp, val);

	return cspell_heal(attacker, target, val);
}

int
spells_cast(dbref attacker, dbref target)
{
	mobi_t *att = MOBI(attacker);
	register unsigned i, d, combo = att->combo;
	unsigned enough_mp = 1;

	for (i = 0; enough_mp && (d = __builtin_ffs(combo)); combo >>= d) {
		switch (spell_cast(attacker, target, (i += d) - 1)) {
		case -1: enough_mp = 0;
			 break;
		case 1:  return 1;
		}
	}

	if (!enough_mp)
		notify(att->who, "Not enough mana.");

	return 0;
}

int
cspell_heal(dbref attacker, dbref target, short amt)
{
	mobi_t *tar = MOBI(target);
	short hp = tar->hp;
	int ret = 0;
	hp += amt;
	if (hp <= 0) {
		hp = 1;
		ret = 1;
		kill_target(attacker, target);
	} else {
		register unsigned short max = HP_MAX(target);
		if (hp > max)
			hp = max;
	}
	tar->hp = hp;
	return ret;
}

