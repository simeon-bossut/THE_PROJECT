-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : mer. 31 mai 2023 à 10:12
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
  `level` int(11) DEFAULT NULL,
  `id_back` int(11) DEFAULT '1',
  `id_dude` int(11) DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `acc`
--

INSERT INTO `acc` (`email`, `pseudo`, `civility`, `password`, `score`, `level`, `id_back`, `id_dude`) VALUES
('admin', 'coucou', 'M', 'azer', NULL, NULL, 1, 1),
('anne.cauche@yahoo.fr', 'Annouchka', 'Mme', 'coucou', NULL, NULL, 1, 1),
('azef@ezf', 'azer', 'M', 'azer', NULL, NULL, 2, 1),
('lucas.verportern@gmail.com', 'Yiroes', 'M', 'Zoeomg', 5000, NULL, 1, 1),
('monkoye@gmail.com', 'monkoyeee', 'M', 'oui', NULL, NULL, 1, 1),
('Paul.antoine@gmail.com', 'PA', 'M', 'oui', NULL, NULL, 1, 1),
('simeon.bossut@gmail.com', 'sim', 'M', 'azer', NULL, NULL, 1, 1),
('test123@gmail.com', 'ceciestuntest', 'M', 'non', 0, 0, 1, 1),
('test2222@gmail.co!', 'TEST', 'M', 'azer', NULL, NULL, 1, 1),
('test@gmail.com', 'test', 'M', 'test', NULL, NULL, 1, 1),
('yanis.ouchene@gmail.com', 'Youyou', 'M', 'mdp', NULL, NULL, 1, 1);

-- --------------------------------------------------------

--
-- Structure de la table `background`
--

CREATE TABLE `background` (
  `id_back` int(11) NOT NULL,
  `url` varchar(40) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `background`
--

INSERT INTO `background` (`id_back`, `url`) VALUES
(1, '../Images/bg_factory.jpg'),
(2, '../Images/bg_factory_chemical.jpg'),
(3, '../Images/bg_factory_neon.jpg'),
(4, '../Images/bg_factory_panda.jpg');

-- --------------------------------------------------------

--
-- Structure de la table `dude`
--

CREATE TABLE `dude` (
  `id_dude` int(11) NOT NULL,
  `url` varchar(40) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

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
  ADD PRIMARY KEY (`id_back`);

--
-- Index pour la table `dude`
--
ALTER TABLE `dude`
  ADD PRIMARY KEY (`id_dude`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
