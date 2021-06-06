-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 06-06-2021 a las 11:33:59
-- Versión del servidor: 10.4.13-MariaDB
-- Versión de PHP: 7.2.31

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `schneider_app`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `elec_meter_list`
--

CREATE TABLE `elec_meter_list` (
  `id` int(64) NOT NULL,
  `sn` int(64) DEFAULT NULL,
  `brand` varchar(128) NOT NULL,
  `model` varchar(128) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `elec_meter_list`
--

INSERT INTO `elec_meter_list` (`id`, `sn`, `brand`, `model`) VALUES
(1, 99000123, 'Schneider', 'P14A'),
(2, 12005987, 'Circutor', 'F37E'),
(3, 54600002, 'unknown', 'unknown'), 
(4, 84000563, 'Itron', 'A12');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `gateway_list`
--

CREATE TABLE `gateway_list` (
  `id` int(64) NOT NULL,
  `sn` int(64) NOT NULL,
  `brand` varchar(128) NOT NULL,
  `model` varchar(128) NOT NULL,
  `ip` varchar(15) NOT NULL,
  `port` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `gateway_list`
--

INSERT INTO `gateway_list` (`id`, `sn`, `brand`, `model`, `ip`, `port`) VALUES
(1, 32000012, 'Samsung', 'T500', '123.456.312.123', 502),
(2, 15007894, 'Asus', 'P12', '154.45.66.4', 0),
(3, 84000564, 'unknown', 'unknown', '192.168.1.12', 802);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `water_meter_list`
--

CREATE TABLE `water_meter_list` (
  `id` int(64) NOT NULL,
  `sn` int(64) NOT NULL,
  `brand` varchar(128) NOT NULL,
  `model` varchar(128) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `water_meter_list`
--

INSERT INTO `water_meter_list` (`id`, `sn`, `brand`, `model`) VALUES
(1, 45100123, 'Emasesa', 'ZA7'),
(2, 54600405, 'unknown', 'unknown'),
(3, 40000447, 'Aqualia', 'P12B'), 
(4, 40000548, 'Aqualia', 'P12A');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `elec_meter_list`
--
ALTER TABLE `elec_meter_list`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `gateway_list`
--
ALTER TABLE `gateway_list`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `water_meter_list`
--
ALTER TABLE `water_meter_list`
  ADD PRIMARY KEY (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
