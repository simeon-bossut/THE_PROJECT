-- phpMyAdmin SQL Dump
-- version 5.1.2
-- https://www.phpmyadmin.net/
--
-- Hôte : localhost:3306
-- Généré le : mar. 16 mai 2023 à 09:44
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
  `password` varchar(36) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `acc`
--

INSERT INTO `acc` (`email`, `pseudo`, `civility`, `password`) VALUES
('Celia@gmail.com', 'Celia', 'M', 'Celiaa2002'),
('Celia@gmail.com', 'Celia', 'M', 'Celiaa2002');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
