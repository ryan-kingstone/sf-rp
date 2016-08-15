-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: 15. Aug, 2016 14:08 p.m.
-- Server-versjon: 10.1.9-MariaDB
-- PHP Version: 5.6.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `sf-rp`
--

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `accounts`
--

CREATE TABLE `accounts` (
  `UserID` int(11) NOT NULL,
  `Username` varchar(42) NOT NULL,
  `Password` varchar(256) NOT NULL,
  `Salt` varchar(72) NOT NULL,
  `Email` varchar(128) NOT NULL,
  `UserRank` varchar(32) NOT NULL,
  `IP` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `businesses`
--

CREATE TABLE `businesses` (
  `BusinessID` int(11) NOT NULL,
  `BusinessName` varchar(64) NOT NULL,
  `BusinessOwnerID` int(11) NOT NULL,
  `BusinessInteriorWorld` int(11) NOT NULL,
  `BusinessExteriorWorld` int(11) NOT NULL,
  `BusinessInterior` tinyint(3) NOT NULL,
  `BusinessInteriorX` float NOT NULL,
  `BusinessInteriorY` float NOT NULL,
  `BusinessInteriorZ` float NOT NULL,
  `BusinessExteriorX` float NOT NULL,
  `BusinessExteriorY` float NOT NULL,
  `BusinessExteriorZ` float NOT NULL,
  `BusinessLocked` tinyint(1) NOT NULL,
  `BusinessPrice` int(11) NOT NULL,
  `BusinessCashbox` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dataark for tabell `businesses`
--

INSERT INTO `businesses` (`BusinessID`, `BusinessName`, `BusinessOwnerID`, `BusinessInteriorWorld`, `BusinessExteriorWorld`, `BusinessInterior`, `BusinessInteriorX`, `BusinessInteriorY`, `BusinessInteriorZ`, `BusinessExteriorX`, `BusinessExteriorY`, `BusinessExteriorZ`, `BusinessLocked`, `BusinessPrice`, `BusinessCashbox`) VALUES
(1, 'Kingpin''s Diner', 0, 12537, 0, 1, 681.419, -447.522, -25.6098, -2351.08, 492.678, 30.8114, 0, 35000, 0);

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `characters`
--

CREATE TABLE `characters` (
  `AccountID` int(11) NOT NULL,
  `Username` varchar(32) NOT NULL,
  `Password` varchar(129) NOT NULL,
  `IP` varchar(32) NOT NULL,
  `GPCIHash` varchar(42) NOT NULL,
  `Money` int(15) NOT NULL,
  `BankMoney` int(11) NOT NULL,
  `Level` int(15) NOT NULL,
  `AdminLevel` int(1) NOT NULL,
  `Faction` tinyint(3) NOT NULL,
  `FactionRank` int(11) NOT NULL,
  `MinutesPlayed` int(11) NOT NULL,
  `ExperiencePoints` int(11) NOT NULL,
  `DonatorLevel` int(1) NOT NULL,
  `Deaths` int(11) NOT NULL,
  `Kills` int(11) NOT NULL,
  `Banned` tinyint(1) NOT NULL,
  `Skin` smallint(4) NOT NULL,
  `CarLicense` tinyint(1) NOT NULL,
  `TruckLicense` tinyint(1) NOT NULL,
  `HeliLicense` tinyint(1) NOT NULL,
  `PlaneLicense` tinyint(1) NOT NULL,
  `MedicalLicense` tinyint(1) NOT NULL,
  `WeaponLicense` tinyint(1) NOT NULL,
  `Job` tinyint(4) NOT NULL,
  `Number` int(11) NOT NULL,
  `RadioChannel` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `clothes`
--

CREATE TABLE `clothes` (
  `ClothingID` int(11) NOT NULL,
  `ModelID` int(11) NOT NULL,
  `BoneID` tinyint(6) NOT NULL,
  `OffsetX` float NOT NULL,
  `OffsetY` float NOT NULL,
  `OffsetZ` float NOT NULL,
  `RotX` float NOT NULL,
  `RotY` float NOT NULL,
  `RotZ` float NOT NULL,
  `ScaleX` float NOT NULL,
  `ScaleY` float NOT NULL,
  `ScaleZ` float NOT NULL,
  `Holder` int(16) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dataark for tabell `clothes`
--

INSERT INTO `clothes` (`ClothingID`, `ModelID`, `BoneID`, `OffsetX`, `OffsetY`, `OffsetZ`, `RotX`, `RotY`, `RotZ`, `ScaleX`, `ScaleY`, `ScaleZ`, `Holder`) VALUES
(9, 18977, 2, 0.048999, 0, 0, 0, 0, 0, 1, 1, 1, 1);

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `corpses`
--

CREATE TABLE `corpses` (
  `CorpseID` int(11) NOT NULL,
  `CorpseVictimID` int(11) NOT NULL,
  `CorpseVictimSkin` smallint(3) NOT NULL,
  `CorpseKillerID` int(11) NOT NULL,
  `CorpseKillerDistance` float NOT NULL,
  `CorpseKillWeapon` tinyint(3) NOT NULL,
  `CorpseStatus` int(1) NOT NULL,
  `CorpseDeathTime` int(11) NOT NULL,
  `CorpseX` float NOT NULL,
  `CorpseY` float NOT NULL,
  `CorpseZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dataark for tabell `corpses`
--

INSERT INTO `corpses` (`CorpseID`, `CorpseVictimID`, `CorpseVictimSkin`, `CorpseKillerID`, `CorpseKillerDistance`, `CorpseKillWeapon`, `CorpseStatus`, `CorpseDeathTime`, `CorpseX`, `CorpseY`, `CorpseZ`) VALUES
(21, 2, 280, 1, 3.63, 23, 0, 1468932132, -1954.67, 139.841, 27.012),
(22, 2, 280, 1, 0.635, 0, 0, 1468932372, -1951.16, 135.681, 26.281),
(23, 1, 295, 1, 0, 127, 0, 1469023360, 0, 0, 0),
(24, 1, 295, 1, 0, 127, 0, 1469026226, 0, 0, 0);

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `factions`
--

CREATE TABLE `factions` (
  `FactionID` int(11) NOT NULL,
  `FactionName` varchar(128) NOT NULL,
  `FactionType` tinyint(1) NOT NULL,
  `FactionShortName` varchar(32) NOT NULL,
  `FactionFlags` varchar(32) NOT NULL,
  `FactionPermissions` varchar(64) NOT NULL,
  `FactionColour` varchar(8) NOT NULL,
  `Rank1` varchar(42) NOT NULL,
  `Rank2` varchar(42) NOT NULL,
  `Rank3` varchar(42) NOT NULL,
  `Rank4` varchar(42) NOT NULL,
  `Rank5` varchar(42) NOT NULL,
  `Rank6` varchar(42) NOT NULL,
  `Rank7` varchar(42) NOT NULL,
  `Rank8` varchar(42) NOT NULL,
  `Rank9` varchar(42) NOT NULL,
  `Rank10` varchar(42) NOT NULL,
  `Rank11` varchar(42) NOT NULL,
  `Rank12` varchar(42) NOT NULL,
  `Rank13` varchar(42) NOT NULL,
  `Rank14` varchar(42) NOT NULL,
  `Rank15` varchar(42) NOT NULL,
  `Rank16` varchar(42) NOT NULL,
  `FactionSpawnX` float NOT NULL DEFAULT '0',
  `FactionSpawnY` float NOT NULL DEFAULT '0',
  `FactionSpawnZ` float NOT NULL DEFAULT '0',
  `FactionSpawnA` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dataark for tabell `factions`
--

INSERT INTO `factions` (`FactionID`, `FactionName`, `FactionType`, `FactionShortName`, `FactionFlags`, `FactionPermissions`, `FactionColour`, `Rank1`, `Rank2`, `Rank3`, `Rank4`, `Rank5`, `Rank6`, `Rank7`, `Rank8`, `Rank9`, `Rank10`, `Rank11`, `Rank12`, `Rank13`, `Rank14`, `Rank15`, `Rank16`, `FactionSpawnX`, `FactionSpawnY`, `FactionSpawnZ`, `FactionSpawnA`) VALUES
(1, 'San Fierro Police Department', 1, 'POLICE', '(gov)', '(fc:1)(sp:1)(gm:6)(um:6)(m:10)', '0198E1', 'Police Officer I', 'Police Officer II', 'Police Officer III', 'Sergeant I', 'Sergeant II', 'Lieutenant', 'Captain', 'Commander', 'Deputy Chief of Police', 'Chief of Police', '', '', '', '', '', '', 0, 0, 0, 0),
(2, 'Criminal Investigation Service', 1, 'CIS', '(gov)(det)', '(fc:1)(sp:1)(gm:8)(um:8)(m:11)', '9C9C9C', 'Junior Field Agent', 'Field Agent I', 'Field Agent II', 'Senior Field Agent', 'Lead Agent', 'Senior Lead Agent', 'Supervisory Agent', 'Executive Agent', 'Assistant Director', 'Deputy Director', 'Director', '', '', '', '', '', -2454.46, 503.976, 30.0786, 280),
(3, 'San Fierro Fire Department', 2, 'SFFD', '(gov)', '(fc:1)(sp:1)(gm:7)(um:7)(m:10)', 'CD5C5C', 'Probationary Firefighter', 'Firefighter I', 'Firefighter II', 'Fire Engineer I', 'Fire Engineer II', 'Lead Engineer', 'Lieutenant', 'Captain', 'Deputy Commissioner', 'Commissioner', '', '', '', '', '', '', 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `inventory`
--

CREATE TABLE `inventory` (
  `ItemID` int(11) NOT NULL,
  `ItemOwnerID` int(11) NOT NULL,
  `ItemType` int(11) NOT NULL,
  `Amount` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dataark for tabell `inventory`
--

INSERT INTO `inventory` (`ItemID`, `ItemOwnerID`, `ItemType`, `Amount`) VALUES
(1, 1, 23, 1),
(6, 1, 29, 10),
(51, 1, 30, 1),
(53, 2, 23, 1),
(55, 1, 20, 19);

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `logs`
--

CREATE TABLE `logs` (
  `LogID` int(11) NOT NULL,
  `LogName` varchar(32) NOT NULL,
  `LogString` varchar(512) NOT NULL,
  `LogPlayer` varchar(32) NOT NULL,
  `LogTimestamp` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Tabellstruktur for tabell `statebuildings`
--

CREATE TABLE `statebuildings` (
  `StateBuildingID` int(11) NOT NULL,
  `StateBuildingName` varchar(64) NOT NULL,
  `StateBuildingFaction` smallint(5) NOT NULL,
  `StateBuildingLocked` tinyint(1) NOT NULL,
  `StateBuildingInteriorWorld` int(11) NOT NULL,
  `StateBuildingExteriorWorld` int(11) NOT NULL,
  `StateBuildingInterior` tinyint(3) NOT NULL,
  `StateBuildingInteriorX` float NOT NULL,
  `StateBuildingInteriorY` float NOT NULL,
  `StateBuildingInteriorZ` float NOT NULL,
  `StateBuildingExteriorX` float NOT NULL,
  `StateBuildingExteriorY` float NOT NULL,
  `StateBuildingExteriorZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellstruktur for tabell `vehicles`
--

CREATE TABLE `vehicles` (
  `VehicleID` int(16) NOT NULL,
  `ModelID` smallint(4) NOT NULL,
  `OwnerID` int(16) NOT NULL,
  `Plate` varchar(11) NOT NULL,
  `Insurance` tinyint(1) NOT NULL,
  `Fuel` float NOT NULL,
  `Traveled` float NOT NULL,
  `VehicleState` double NOT NULL,
  `Colour1` tinyint(4) NOT NULL,
  `Colour2` tinyint(4) NOT NULL,
  `ParkedX` float NOT NULL,
  `ParkedY` float NOT NULL,
  `ParkedZ` float NOT NULL,
  `ParkedA` float NOT NULL,
  `Nitrous` int(11) NOT NULL,
  `Hydraulics` int(11) NOT NULL,
  `Wheels` int(11) NOT NULL,
  `Siren` tinyint(1) NOT NULL,
  `VehiclePanels` int(11) NOT NULL,
  `VehicleDoors` int(11) NOT NULL,
  `VehicleLights` int(11) NOT NULL,
  `VehicleTires` int(11) NOT NULL,
  `Broken` tinyint(1) NOT NULL,
  `Faction` int(11) NOT NULL,
  `Carsign` varchar(64) NOT NULL,
  `Type` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dataark for tabell `vehicles`
--

INSERT INTO `vehicles` (`VehicleID`, `ModelID`, `OwnerID`, `Plate`, `Insurance`, `Fuel`, `Traveled`, `VehicleState`, `Colour1`, `Colour2`, `ParkedX`, `ParkedY`, `ParkedZ`, `ParkedA`, `Nitrous`, `Hydraulics`, `Wheels`, `Siren`, `VehiclePanels`, `VehicleDoors`, `VehicleLights`, `VehicleTires`, `Broken`, `Faction`, `Carsign`, `Type`) VALUES
(1, 426, 1, 'LKN-398', 3, 100, 0, 100, 1, 1, -1987.95, 125.091, 27.191, 180.417, 3, 1, 8, 0, 0, 0, 0, 0, 0, 0, '', 1),
(2, 521, 1, 'ADG-523', 3, 100, 0, 100, 3, 1, -1986.94, 141.493, 27.1044, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 1),
(3, 438, 1, 'PSX-487', 3, 100, 0, 100, 6, 6, -1987.97, 132.975, 27.5436, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, '', 1),
(4, 597, 0, 'BXE-062', 4, 100, 0, 100, 0, 1, -1573.65, 706.107, -5.626, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 'A1', 2),
(5, 521, 2, 'LCN-362', 3, 100, 0, 100, 3, 1, -1986.94, 149.493, 27.1044, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 1),
(6, 597, 0, 'LXJ-329', 4, 100, 0, 100, 0, 1, -1573.6, 710.149, -5.627, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 'A2', 2),
(7, 426, 0, 'JSW-142', 4, 100, 0, 100, 0, 0, -1596.52, 676.246, -5.586, 359.273, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, '', 1),
(8, 599, 0, 'TTN-494', 4, 100, 0, 100, 0, 1, -1590.36, 705.7, -5.045, 269.302, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 'B1', 2),
(9, 597, 0, 'IBH-067', 4, 100, 0, 100, 0, 1, -1573.46, 714.263, -5.747, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 'A3', 2),
(10, 597, 0, 'QOG-377', 4, 100, 0, 100, 0, 1, -1573.45, 718.372, -5.747, 90.838, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 'A4', 2),
(11, 497, 0, 'SE1-PD1', 4, 100, 0, 100, 0, 1, -1679.88, 705.69, 30.778, 88.64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 'SE1SFPD', 1),
(12, 426, 0, 'ANC-575', 4, 100, 0, 100, 0, 0, -2429.71, 515.382, 29.586, 216.69, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(13, 426, 0, 'NOI-711', 4, 100, 0, 100, 0, 0, -2425.89, 518.488, 29.579, 222.452, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(14, 560, 0, 'ETV-655', 4, 100, 0, 100, 0, 0, -2422.3, 521.659, 29.635, 225.939, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(15, 560, 0, 'QRB-142', 4, 100, 0, 100, 0, 0, -2419.16, 525.048, 29.635, 231.637, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(16, 579, 0, 'DSO-268', 4, 100, 0, 100, 0, 0, -2416.8, 528.56, 29.864, 239.024, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(17, 490, 0, 'OGI-932', 4, 100, 0, 100, 0, 0, -2443.23, 531.904, 30.042, 180.794, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(18, 490, 0, 'WMN-344', 4, 100, 0, 100, 0, 0, -2439.04, 532.003, 30.032, 179.33, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(19, 455, 0, 'BXC-719', 4, 100, 0, 100, 1, 1, -2438.4, 515.608, 30.347, 181.184, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(20, 579, 0, 'BRS-459', 4, 100, 0, 100, 0, 0, -2415.19, 532.067, 29.921, 247.89, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(21, 402, 0, 'UFP-533', 4, 100, 0, 100, 0, 0, -2414.17, 535.852, 29.708, 257.548, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(22, 402, 0, 'VRU-726', 4, 100, 0, 100, 0, 0, -2413.99, 539.932, 29.998, 268.734, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(23, 487, 0, 'WCO-745', 4, 100, 0, 100, 0, 0, -2472.96, 491.717, 30.241, 279.01, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, '', 1),
(24, 521, 0, 'CJH-524', 4, 100, 0, 100, 0, 0, -2434.17, 509.352, 29.5, 111.719, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, '', 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`UserID`);

--
-- Indexes for table `businesses`
--
ALTER TABLE `businesses`
  ADD PRIMARY KEY (`BusinessID`);

--
-- Indexes for table `characters`
--
ALTER TABLE `characters`
  ADD PRIMARY KEY (`AccountID`);

--
-- Indexes for table `clothes`
--
ALTER TABLE `clothes`
  ADD PRIMARY KEY (`ClothingID`);

--
-- Indexes for table `corpses`
--
ALTER TABLE `corpses`
  ADD PRIMARY KEY (`CorpseID`);

--
-- Indexes for table `factions`
--
ALTER TABLE `factions`
  ADD PRIMARY KEY (`FactionID`);

--
-- Indexes for table `inventory`
--
ALTER TABLE `inventory`
  ADD PRIMARY KEY (`ItemID`);

--
-- Indexes for table `logs`
--
ALTER TABLE `logs`
  ADD PRIMARY KEY (`LogID`);

--
-- Indexes for table `statebuildings`
--
ALTER TABLE `statebuildings`
  ADD PRIMARY KEY (`StateBuildingID`);

--
-- Indexes for table `vehicles`
--
ALTER TABLE `vehicles`
  ADD PRIMARY KEY (`VehicleID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `accounts`
--
ALTER TABLE `accounts`
  MODIFY `UserID` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `businesses`
--
ALTER TABLE `businesses`
  MODIFY `BusinessID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT for table `characters`
--
ALTER TABLE `characters`
  MODIFY `AccountID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT for table `clothes`
--
ALTER TABLE `clothes`
  MODIFY `ClothingID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;
--
-- AUTO_INCREMENT for table `corpses`
--
ALTER TABLE `corpses`
  MODIFY `CorpseID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;
--
-- AUTO_INCREMENT for table `factions`
--
ALTER TABLE `factions`
  MODIFY `FactionID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `inventory`
--
ALTER TABLE `inventory`
  MODIFY `ItemID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=56;
--
-- AUTO_INCREMENT for table `logs`
--
ALTER TABLE `logs`
  MODIFY `LogID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT for table `statebuildings`
--
ALTER TABLE `statebuildings`
  MODIFY `StateBuildingID` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `vehicles`
--
ALTER TABLE `vehicles`
  MODIFY `VehicleID` int(16) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
