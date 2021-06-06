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
(1, 1123, 'unknown', 'unknown'),
(2, 74567, 'unknown', 'unknown'),
(3, 2354, 'unknown', 'unknown'),
(4, 1234, 'Siemens', 'P50F'),
(5, 12, 'unknown', 'unknown'),
(6, 6534, 'unknown', 'unknown');

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
(1, 456123, 'Samsung', 'T500', '123.456.312.123', 502),
(2, 123, 'unknown', 'unknown', '1.1.1.1', 1),
(3, 5624, 'Asus', 'P12', '154.45.66.4', 564),
(4, 98, 'unknown', 'unknown', '1.1.1.2', 123);

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
(1, 1234, 'Siemens', 'P14A'),
(2, 245, 'unknown', 'unknown'),
(3, 1235, 'Siemens', 'P14A'),
(4, 776, 'unknown', 'unknown');

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
