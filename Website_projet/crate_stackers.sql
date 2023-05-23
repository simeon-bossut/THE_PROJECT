-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : mar. 23 mai 2023 à 15:21
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
  `password` varchar(36) NOT NULL,
  `score` int(11) DEFAULT NULL,
  `level` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `acc`
--

INSERT INTO `acc` (`email`, `pseudo`, `civility`, `password`, `score`, `level`) VALUES
('admin', 'coucpou', 'M', 'coucou', NULL, NULL),
('anne.cauche@yahoo.fr', 'Annouchka', 'Mme', 'coucou', NULL, NULL),
('azef@ezf', 'azer', 'M', 'azer', NULL, NULL),
('lucas.verportern@gmail.com', 'Yiroes', 'M', 'Zoeomg', 5000, NULL),
('Paul.antoine@gmail.com', 'PA', 'M', 'oui', NULL, NULL),
('simeon.bossut@gmail.com', 'sim', 'M', 'azer', NULL, NULL),
('test123@gmail.com', 'ceciestuntest', 'M', 'non', 0, 0),
('test2222@gmail.co!', 'TEST', 'M', 'azer', NULL, NULL),
('test@gmail.com', 'test', 'M', 'test', NULL, NULL),
('yanis.ouchene@gmail.com', 'Youyou', 'M', 'mdp', NULL, NULL);

-- --------------------------------------------------------

--
-- Structure de la table `custom`
--

CREATE TABLE `custom` (
  `id` int(11) NOT NULL,
  `url` varchar(36) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `acc`
--
ALTER TABLE `acc`
  ADD PRIMARY KEY (`email`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
