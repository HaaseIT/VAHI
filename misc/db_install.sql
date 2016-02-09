-- phpMyAdmin SQL Dump
-- version 3.3.5.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Erstellungszeit: 23. September 2010 um 16:31
-- Server Version: 5.0.51
-- PHP-Version: 5.2.4-2ubuntu5.10

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Datenbank: `haase-image-pss-dev`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `categories`
--

CREATE TABLE IF NOT EXISTS `categories` (
  `cat_id` int(11) NOT NULL auto_increment,
  `cat_advsearch` char(1) NOT NULL default '',
  `cat_order` int(4) NOT NULL default '0',
  `cat_selectwidth` int(4) NOT NULL default '0',
  PRIMARY KEY  (`cat_id`),
  UNIQUE KEY `cat_order` (`cat_order`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `categories_lang`
--

CREATE TABLE IF NOT EXISTS `categories_lang` (
  `cl_id` int(11) NOT NULL auto_increment,
  `cl_cid` int(11) NOT NULL default '0',
  `cl_lang` char(2) NOT NULL default '',
  `cl_string` varchar(32) NOT NULL default '',
  PRIMARY KEY  (`cl_id`),
  KEY `cl_cid` (`cl_cid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `comments`
--

CREATE TABLE IF NOT EXISTS `comments` (
  `com_id` int(11) NOT NULL auto_increment,
  `com_fid` int(11) NOT NULL default '0',
  `com_lang` char(2) NOT NULL default '',
  `com_html` text NOT NULL,
  PRIMARY KEY  (`com_id`),
  KEY `com_fid` (`com_fid`),
  KEY `com_lang` (`com_lang`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `files`
--

CREATE TABLE IF NOT EXISTS `files` (
  `fil_id` int(11) NOT NULL auto_increment,
  `fil_path` varchar(128) NOT NULL default '',
  `fil_name` varchar(64) NOT NULL default '',
  `fil_user` int(11) NOT NULL default '0',
  PRIMARY KEY  (`fil_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=73 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `keywords`
--

CREATE TABLE IF NOT EXISTS `keywords` (
  `key_id` int(11) NOT NULL auto_increment,
  `key_category` int(11) NOT NULL default '0',
  PRIMARY KEY  (`key_id`),
  KEY `key_category` (`key_category`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=199 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `keywords_lang`
--

CREATE TABLE IF NOT EXISTS `keywords_lang` (
  `kl_id` int(11) NOT NULL auto_increment,
  `kl_kid` int(11) NOT NULL default '0',
  `kl_lang` char(2) NOT NULL default '',
  `kl_string` varchar(32) NOT NULL default '',
  PRIMARY KEY  (`kl_id`),
  KEY `kl_kid` (`kl_kid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=375 ;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `matches`
--

CREATE TABLE IF NOT EXISTS `matches` (
  `mat_fid` int(11) NOT NULL default '0',
  `mat_kid` int(11) NOT NULL default '0',
  KEY `mat_fid` (`mat_fid`),
  KEY `mat_kid` (`mat_kid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `users`
--

CREATE TABLE IF NOT EXISTS `users` (
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
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;
