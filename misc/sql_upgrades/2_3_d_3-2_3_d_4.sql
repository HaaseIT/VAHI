CREATE TABLE `categories_lang` (
`cl_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`cl_cid` INT NOT NULL ,
`cl_lang` CHAR( 2 ) NOT NULL ,
`cl_string` VARCHAR( 32 ) NOT NULL ,
INDEX ( `cl_cid` )
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

INSERT INTO categories_lang (cl_cid, cl_string, cl_lang)
SELECT cat_id, cat_name, 'en' FROM categories;

ALTER TABLE `categories`
  DROP `cat_name`;

CREATE TABLE `keywords_lang` (
`kl_id` INT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`kl_kid` INT NOT NULL ,
`kl_lang` CHAR( 2 ) NOT NULL ,
`kl_string` VARCHAR( 32 ) NOT NULL ,
INDEX ( `kl_kid` )
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

INSERT INTO keywords_lang (kl_kid, kl_string, kl_lang)
SELECT key_id, key_name, 'en' FROM keywords;

ALTER TABLE `keywords`
  DROP `key_name`;