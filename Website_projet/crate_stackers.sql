-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jun 07, 2023 at 09:29 AM
-- Server version: 5.7.24
-- PHP Version: 8.0.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `crate_stackers`
--

-- --------------------------------------------------------

--
-- Table structure for table `acc`
--

CREATE TABLE `acc` (
  `email` varchar(36) NOT NULL,
  `admin` tinyint(1) DEFAULT NULL,
  `pseudo` varchar(36) NOT NULL,
  `civility` varchar(12) NOT NULL,
  `password` varchar(64) NOT NULL,
  `score` int(11) DEFAULT NULL,
  `level` int(11) DEFAULT NULL,
  `id_back` int(11) DEFAULT '1',
  `id_dude` int(11) DEFAULT '1',
  `id_hat` int(2) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acc`
--

INSERT INTO `acc` (`email`, `admin`, `pseudo`, `civility`, `password`, `score`, `level`, `id_back`, `id_dude`, `id_hat`) VALUES
('admin', 0, 'coucou', 'M', 'azer', NULL, NULL, 1, 10, 13),
('anne.cauche@yahoo.fr', 0, 'Annouchka', 'Mme', 'coucou', NULL, NULL, 0, 1, 0),
('azef@ezf', 0, 'azer', 'M', 'azer', NULL, NULL, 0, 1, 0),
('lucas.verportern@gmail.com', 0, 'Yiroes', 'M', 'Zoeomg', 5000, NULL, 0, 1, 0),
('monkoye@gmail.com', 0, 'monkoyeee', 'M', 'oui', NULL, NULL, 0, 1, 0),
('nouveau_compte@gmail.compte', 0, 'XxdestructorxX', 'M', 'f5c984202b3b0eb868a39a0287e9e2aee6920018', NULL, NULL, 1, 1, 0),
('Paul.antoine@gmail.com', 0, 'PA', 'M', 'oui', NULL, NULL, 0, 1, 0),
('simeon.bossut@gmail.com', 0, 'sim', 'M', 'azer', NULL, NULL, 0, 1, 0),
('simon@gmail.com', 1, 'Simowo', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', NULL, NULL, 2, 4, 3),
('test123@gmail.com', 0, 'ceciestuntest', 'M', 'non', 0, 0, 0, 1, 0),
('test2222@gmail.co!', 0, 'TEST', 'M', 'azer', NULL, NULL, 0, 1, 0),
('test@gmail.com', 0, 'test', 'M', 'test', NULL, NULL, 0, 1, 0),
('test@test.test', NULL, 'test', 'M', '5e52fee47e6b070565f74372468cdc699de89107', NULL, NULL, 1, 1, 0),
('yanis.ouchene@gmail.com', 0, 'Youyou', 'M', 'mdp', NULL, NULL, 0, 1, 0);

-- --------------------------------------------------------

--
-- Table structure for table `background`
--

CREATE TABLE `background` (
  `id` int(11) NOT NULL,
  `url` varchar(40) NOT NULL,
  `name` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `background`
--

INSERT INTO `background` (`id`, `url`, `name`) VALUES
(1, 'bg_factory', 'Classic'),
(2, 'bg_factory_chemical', 'Chemical'),
(3, 'bg_factory_neon', 'Neon'),
(4, 'bg_factory_panda', '???');

-- --------------------------------------------------------

--
-- Table structure for table `body`
--

CREATE TABLE `body` (
  `id` int(2) NOT NULL,
  `url` varchar(64) NOT NULL,
  `name` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `body`
--

INSERT INTO `body` (`id`, `url`, `name`) VALUES
(1, 'character_default', 'Default'),
(2, 'red', 'Red'),
(3, 'blue', 'Blue'),
(4, 'green', 'Green'),
(5, 'orange', 'Orange'),
(6, 'purple', 'Purple'),
(7, 'yellow', 'Yellow'),
(8, 'cyan', 'Aqua'),
(9, 'plus_minus', 'Plus Minus'),
(10, 'crate_body', 'Crate Camo');

-- --------------------------------------------------------

--
-- Table structure for table `hat`
--

CREATE TABLE `hat` (
  `id` int(2) NOT NULL,
  `url` varchar(64) NOT NULL,
  `name` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `hat`
--

INSERT INTO `hat` (`id`, `url`, `name`) VALUES
(1, 'audio_helmet', 'Headset'),
(2, 'aureole', 'Aureole'),
(3, 'biker_helmet', 'Biker Helmet'),
(4, 'cap', 'Cap'),
(5, 'corns', 'Bull Horns'),
(6, 'cowboy_hat', 'Cowboy Hat'),
(7, 'crown', 'Crown'),
(8, 'drink_cap', 'Drink Helmet'),
(9, 'gold_robot', 'Gold Robot'),
(10, 'miner_helmet', 'Mining Helmet'),
(11, 'silver_robot', 'Silver Robot'),
(12, 'viking_helmet', 'Viking Helmet'),
(13, 'work_helmet', 'Construction Helmet');

-- --------------------------------------------------------

--
-- Table structure for table `level`
--

CREATE TABLE `level` (
  `email` varchar(36) NOT NULL,
  `id` int(11) NOT NULL,
  `nom` varchar(20) NOT NULL,
  `seed` varchar(32) NOT NULL,
  `difficulty` varchar(10) NOT NULL,
  `dim` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `report`
--

CREATE TABLE `report` (
  `id` int(11) NOT NULL,
  `type` varchar(8) NOT NULL,
  `text` varchar(1000) NOT NULL,
  `date` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `report`
--

INSERT INTO `report` (`id`, `type`, `text`, `date`) VALUES
(7, 'idea', 'idée avec un id', '2023-06-06'),
(8, 'bug', 'tetttes', '2023-06-06'),
(10, 'idea', 'idee', '2023-06-06');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `acc`
--
ALTER TABLE `acc`
  ADD PRIMARY KEY (`email`);

--
-- Indexes for table `background`
--
ALTER TABLE `background`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `body`
--
ALTER TABLE `body`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `hat`
--
ALTER TABLE `hat`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `level`
--
ALTER TABLE `level`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `report`
--
ALTER TABLE `report`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `body`
--
ALTER TABLE `body`
  MODIFY `id` int(2) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `hat`
--
ALTER TABLE `hat`
  MODIFY `id` int(2) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `level`
--
ALTER TABLE `level`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `report`
--
ALTER TABLE `report`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
