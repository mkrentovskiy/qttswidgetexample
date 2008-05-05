DROP TABLE IF EXISTS `devices`;
CREATE TABLE `devices` (
  `id` varchar(8) collate utf8_unicode_ci NOT NULL,
  `title` varchar(16) collate utf8_unicode_ci NOT NULL,
  `ip` varchar(16) collate utf8_unicode_ci NOT NULL,
  `port` int(5) NOT NULL default '8888',
  `x` float NOT NULL,
  `y` float NOT NULL,
  `color` varchar(11) collate utf8_unicode_ci NOT NULL,
  `comment` varchar(255) collate utf8_unicode_ci NOT NULL,
  `maxv` float NOT NULL,
  `minh` float NOT NULL,
  `maxh` float NOT NULL,
  `is_h` tinyint(1) NOT NULL,
  `type` tinyint(1) NOT NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `title` (`title`),
  KEY `ip` (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


INSERT INTO `devices` (`id`, `title`, `ip`, `port`, `x`, `y`, `color`, `comment`, `maxv`, `minh`, `maxh`, `is_h`, `type`) VALUES 
('SH1', 'ИП1', '127.0.0.1', 8888, 11, 10, '#0ff', '', 1, 1.5, 15, 0, 4),
('IP2', 'ИП2', '127.0.0.1', 8888, 6, 5, '#f00', '', 10, 0, 10, 0, 3);
