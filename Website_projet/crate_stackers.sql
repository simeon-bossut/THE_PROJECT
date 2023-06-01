-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : jeu. 01 juin 2023 à 09:13
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
  `pseudo` varchar(36) NOT NULL,
  `civility` varchar(12) NOT NULL,
  `password` varchar(36) NOT NULL,
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
('admin', 'coucou', 'M', 'azer', NULL, NULL, 1, 1, 5),
('anne.cauche@yahoo.fr', 'Annouchka', 'Mme', 'coucou', NULL, NULL, 1, 1, 0),
('azef@ezf', 'azer', 'M', 'azer', NULL, NULL, 2, 1, 0),
('lucas.verportern@gmail.com', 'Yiroes', 'M', 'Zoeomg', 5000, NULL, 1, 1, 0),
('monkoye@gmail.com', 'monkoyeee', 'M', 'oui', NULL, NULL, 1, 1, 0),
('Paul.antoine@gmail.com', 'PA', 'M', 'oui', NULL, NULL, 1, 1, 0),
('simeon.bossut@gmail.com', 'sim', 'M', 'azer', NULL, NULL, 1, 1, 0),
('test123@gmail.com', 'ceciestuntest', 'M', 'non', 0, 0, 1, 1, 0),
('test2222@gmail.co!', 'TEST', 'M', 'azer', NULL, NULL, 1, 1, 0),
('test@gmail.com', 'test', 'M', 'test', NULL, NULL, 1, 1, 0),
('yanis.ouchene@gmail.com', 'Youyou', 'M', 'mdp', NULL, NULL, 1, 1, 0);

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
-- Structure de la table `body`
--

CREATE TABLE `body` (
  `id` int(2) NOT NULL,
  `url` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `hat`
--

CREATE TABLE `hat` (
  `id` int(2) NOT NULL,
  `url` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `hat`
--

INSERT INTO `hat` (`id`, `url`) VALUES
(1, 'audio_helmet'),
(2, 'aureole'),
(3, 'biker_helmet'),
(4, 'cap'),
(5, 'corns'),
(6, 'cowboy_hat'),
(7, 'crown'),
(8, 'drink_cap'),
(9, 'gold_robot'),
(10, 'miner_helmet'),
(11, 'silver_robot'),
(12, 'viking_helmet'),
(13, 'work_helemt');

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
  MODIFY `id` int(2) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT pour la table `hat`
--
ALTER TABLE `hat`
  MODIFY `id` int(2) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
