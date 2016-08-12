-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: 20. Jul, 2016 20:32 p.m.
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


-- --------------------------------------------------------

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
  MODIFY `BusinessID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT for table `characters`
--
ALTER TABLE `characters`
  MODIFY `AccountID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT for table `clothes`
--
ALTER TABLE `clothes`
  MODIFY `ClothingID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT for table `corpses`
--
ALTER TABLE `corpses`
  MODIFY `CorpseID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT for table `factions`
--
ALTER TABLE `factions`
  MODIFY `FactionID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
--
-- AUTO_INCREMENT for table `inventory`
--
ALTER TABLE `inventory`
  MODIFY `ItemID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
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
  MODIFY `VehicleID` int(16) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
