-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : ven. 02 juin 2023 à 08:58
-- Version du serveur : 5.7.24
-- Version de PHP : 7.4.16

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

INSERT INTO `acc` (`email`, `pseudo`, `civility`, `password`, `score`, `level`, `id_back`, `id_dude`, `id_hat`) VALUES
('admin', 'coucou', 'M', 'azer', NULL, NULL, 1, 10, 13),
('anne.cauche@yahoo.fr', 'Annouchka', 'Mme', 'coucou', NULL, NULL, 0, 1, 0),
('azef@ezf', 'azer', 'M', 'azer', NULL, NULL, 0, 1, 0),
('lucas.verportern@gmail.com', 'Yiroes', 'M', 'Zoeomg', 5000, NULL, 0, 1, 0),
('monkoye@gmail.com', 'monkoyeee', 'M', 'oui', NULL, NULL, 0, 1, 0),
('nouveau_compte@gmail.compte', 'XxdestructorxX', 'M', 'f5c984202b3b0eb868a39a0287e9e2aee6920018', NULL, NULL, 1, 1, 0),
('Paul.antoine@gmail.com', 'PA', 'M', 'oui', NULL, NULL, 0, 1, 0),
('simeon.bossut@gmail.com', 'sim', 'M', 'azer', NULL, NULL, 0, 1, 0),
('test123@gmail.com', 'ceciestuntest', 'M', 'non', 0, 0, 0, 1, 0),
('test2222@gmail.co!', 'TEST', 'M', 'azer', NULL, NULL, 0, 1, 0),
('test@gmail.com', 'test', 'M', 'test', NULL, NULL, 0, 1, 0),
('yanis.ouchene@gmail.com', 'Youyou', 'M', 'mdp', NULL, NULL, 0, 1, 0);

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
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
