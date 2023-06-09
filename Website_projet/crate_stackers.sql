-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : ven. 09 juin 2023 à 12:32
-- Version du serveur : 5.7.24
-- Version de PHP : 8.0.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `crate_stackers`
--

-- --------------------------------------------------------

--
-- Structure de la table `acc`
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
-- Déchargement des données de la table `acc`
--

INSERT INTO `acc` (`email`, `admin`, `pseudo`, `civility`, `password`, `score`, `level`, `id_back`, `id_dude`, `id_hat`) VALUES
('arsial@gmail.com', 1, 'Arsial', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', 17089, NULL, 4, 9, 10),
('destructor@gmail.com', NULL, 'XxdestructorxX', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', 266, NULL, 3, 4, 9),
('paulantoine@gmail.com', 1, 'PA', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', 65020, NULL, 2, 10, 7),
('paulmaurice.cauche@gmail.com', 1, 'Monkoye', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', 1350, NULL, 1, 8, 4),
('simeon.bossut@gmail.com', 1, 'simeme', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', 1287, NULL, 1, 6, 6),
('simon@gmail.com', 1, 'Simowo', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', 29806, NULL, 2, 2, 5),
('yanis.ouchn@gmail.com', 1, 'Yanou', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', 1320, NULL, 3, 3, 13),
('youremail@gmail.com', NULL, 'Pseudo', 'M', '1892d91129a24f0948ecf369dd28034f703ce907', 7883, NULL, 2, 7, 11);

-- --------------------------------------------------------

--
-- Structure de la table `background`
--

CREATE TABLE `background` (
  `id` int(11) NOT NULL,
  `url` varchar(40) NOT NULL,
  `name` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `background`
--

INSERT INTO `background` (`id`, `url`, `name`) VALUES
(1, 'bg_factory', 'Classic'),
(2, 'bg_factory_chemical', 'Chemical'),
(3, 'bg_factory_neon', 'Neon'),
(4, 'bg_factory_panda', '???');

-- --------------------------------------------------------

--
-- Structure de la table `body`
--

CREATE TABLE `body` (
  `id` int(2) NOT NULL,
  `url` varchar(64) NOT NULL,
  `name` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `body`
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
-- Structure de la table `hat`
--

CREATE TABLE `hat` (
  `id` int(2) NOT NULL,
  `url` varchar(64) NOT NULL,
  `name` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `hat`
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
-- Structure de la table `level`
--

CREATE TABLE `level` (
  `email` varchar(36) NOT NULL,
  `id` int(11) NOT NULL,
  `nom` varchar(20) NOT NULL,
  `seed` varchar(32) NOT NULL,
  `dim` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `level`
--

INSERT INTO `level` (`email`, `id`, `nom`, `seed`, `dim`) VALUES
('simon@gmail.com', 1, 'mon niveau test', '0000000000', '3x3'),
('arsial@gmail.com', 2, 'Official PFD', '4230108180000028420', '4'),
('arsial@gmail.com', 3, 'SwitchCrate', '34510081058', '3'),
('arsial@gmail.com', 4, 'PokeBall', '4031120160000065535', '4'),
('arsial@gmail.com', 5, 'Cauchemar Trkl', '4111603200819629356', '4'),
('arsial@gmail.com', 6, 'Cauchemar', '4170110190001655601', '4');

-- --------------------------------------------------------

--
-- Structure de la table `report`
--

CREATE TABLE `report` (
  `id` int(11) NOT NULL,
  `type` varchar(8) NOT NULL,
  `text` varchar(1000) NOT NULL,
  `date` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `report`
--

INSERT INTO `report` (`id`, `type`, `text`, `date`) VALUES
(7, 'idea', 'idée avec un id', '2023-06-06'),
(8, 'bug', 'tetttes', '2023-06-06'),
(10, 'idea', 'idee', '2023-06-06');

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `acc`
--
ALTER TABLE `acc`
  ADD PRIMARY KEY (`email`);

--
-- Index pour la table `background`
--
ALTER TABLE `background`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `body`
--
ALTER TABLE `body`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `hat`
--
ALTER TABLE `hat`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `level`
--
ALTER TABLE `level`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `report`
--
ALTER TABLE `report`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `body`
--
ALTER TABLE `body`
  MODIFY `id` int(2) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT pour la table `hat`
--
ALTER TABLE `hat`
  MODIFY `id` int(2) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT pour la table `level`
--
ALTER TABLE `level`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT pour la table `report`
--
ALTER TABLE `report`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
