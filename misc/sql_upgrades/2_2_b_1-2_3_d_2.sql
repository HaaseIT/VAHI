ALTER TABLE matches
ADD INDEX (mat_kid),
ADD INDEX (mat_fid);

ALTER TABLE comments
ADD INDEX (com_fid),
ADD INDEX (com_lang);

ALTER TABLE keywords
ADD INDEX (key_category);
