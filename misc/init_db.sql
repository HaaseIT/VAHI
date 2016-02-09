-- 
-- Tabellenstruktur für Tabelle `categories`
-- 

CREATE TABLE `categories` (
  `cat_id` int(11) NOT NULL auto_increment,
  `cat_name` varchar(32) NOT NULL default '',
  `cat_advsearch` char(1) NOT NULL default '',
  `cat_order` int(4) NOT NULL default '0',
  `cat_selectwidth` int(4) NOT NULL default '0',
  PRIMARY KEY  (`cat_id`),
  UNIQUE KEY `cat_order` (`cat_order`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Tabellenstruktur für Tabelle `comments`
-- 

CREATE TABLE `comments` (
  `com_id` int(11) NOT NULL auto_increment,
  `com_fid` int(11) NOT NULL default '0',
  `com_lang` char(2) NOT NULL default '',
  `com_html` text NOT NULL,
  PRIMARY KEY  (`com_id`),
  KEY `com_fid` (`com_fid`),
  KEY `com_lang` (`com_lang`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Tabellenstruktur für Tabelle `files`
-- 

CREATE TABLE `files` (
  `fil_id` int(11) NOT NULL auto_increment,
  `fil_path` varchar(128) NOT NULL default '',
  `fil_name` varchar(64) NOT NULL default '',
  `fil_user` int(11) NOT NULL default '0',
  PRIMARY KEY  (`fil_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Tabellenstruktur für Tabelle `keywords`
-- 

CREATE TABLE `keywords` (
  `key_id` int(11) NOT NULL auto_increment,
  `key_name` varchar(32) NOT NULL default '',
  `key_category` int(11) NOT NULL default '0',
  PRIMARY KEY  (`key_id`),
  KEY `key_category` (`key_category`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Tabellenstruktur für Tabelle `matches`
-- 

CREATE TABLE `matches` (
  `mat_fid` int(11) NOT NULL default '0',
  `mat_kid` int(11) NOT NULL default '0',
  KEY `mat_fid` (`mat_fid`),
  KEY `mat_kid` (`mat_kid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

-- 
-- Tabellenstruktur für Tabelle `users`
-- 

CREATE TABLE `users` (
  `usr_id` int(11) NOT NULL auto_increment,
  `usr_name` varchar(128) NOT NULL default '',
  `usr_address` text NOT NULL,
  `usr_filetext` tinytext NOT NULL,
  `usr_comment` text NOT NULL,
  `usr_login` varchar(16) NOT NULL default '',
  `usr_password` varchar(32) NOT NULL default '',
  `usr_class` int(4) NOT NULL default '0',
  `usr_visibility` int(11) NOT NULL default '0',
  `usr_pref_showallimages` tinyint(4) NOT NULL default '0',
  `usr_pref_adminposition` tinyint(4) NOT NULL default '0',
  `usr_pref_showhidden` tinyint(4) NOT NULL default '0',
  `usr_pref_showdate` tinyint(4) NOT NULL default '0',
  `usr_pref_showdimensions` tinyint(4) NOT NULL default '0',
  `usr_pref_showfilesize` tinyint(4) NOT NULL default '0',
  `usr_pref_shownav` tinyint(4) NOT NULL default '1',
  `usr_pref_showfiles` tinyint(4) NOT NULL default '0',
  `usr_pref_override_rowscols` tinyint(4) NOT NULL default '0',
  `usr_pref_thumbsrows` tinyint(4) NOT NULL default '4',
  `usr_pref_thumbscols` tinyint(4) NOT NULL default '5',
  `usr_pref_showdiradmin` tinyint(4) NOT NULL default '1',
  PRIMARY KEY  (`usr_id`),
  UNIQUE KEY `usr_login` (`usr_login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
