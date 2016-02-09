ALTER TABLE users
ADD usr_pref_showhidden TINYINT NOT NULL DEFAULT '0',
ADD usr_pref_showdate TINYINT NOT NULL DEFAULT '0',
ADD usr_pref_showdimensions TINYINT NOT NULL DEFAULT '0',
ADD usr_pref_showfilesize TINYINT NOT NULL DEFAULT '0',
ADD usr_pref_shownav TINYINT NOT NULL DEFAULT '1',
ADD usr_pref_showfiles TINYINT NOT NULL DEFAULT '0',
ADD `usr_pref_override_rowscols` TINYINT NOT NULL DEFAULT '0',
ADD `usr_pref_thumbsrows` TINYINT NOT NULL DEFAULT '4',
ADD `usr_pref_thumbscols` TINYINT NOT NULL DEFAULT '5',
ADD `usr_pref_showdiradmin` TINYINT NOT NULL DEFAULT '1';
