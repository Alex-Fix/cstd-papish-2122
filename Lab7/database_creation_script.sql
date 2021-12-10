
DROP TABLE IF EXISTS `Addresses`;
CREATE TABLE `Addresses` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Street` longtext CHARACTER SET utf8mb4 NOT NULL,
  `HouseNumber` longtext CHARACTER SET utf8mb4 NOT NULL,
  `AppNumber` longtext CHARACTER SET utf8mb4,
  `PostIndex` longtext CHARACTER SET utf8mb4,
  `CityId` int(11) NOT NULL,
  `DeliveryOption` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`),
  KEY `IX_Addresses_CityId` (`CityId`),
  CONSTRAINT `FK_Addresses_Cities_CityId` FOREIGN KEY (`CityId`) REFERENCES `Cities` (`Id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=71 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Cities`;

CREATE TABLE `Cities` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` longtext CHARACTER SET utf8mb4 NOT NULL,
  `SWLat` double NOT NULL,
  `SWLng` double NOT NULL,
  `NELat` double NOT NULL,
  `NELng` double NOT NULL,
  `PlacesOfUseId` int(11) NOT NULL DEFAULT '0',
  `DeliveryType` int(11) NOT NULL DEFAULT '20',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=2594 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `CitySchedules`;

CREATE TABLE `CitySchedules` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `TrainId` int(11) NOT NULL,
  `ScheduleId` int(11) NOT NULL,
  `DepartureCityId` int(11) NOT NULL DEFAULT '0',
  `DestinationCityId` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`),
  KEY `FK_CitySchedules_Schedules_ScheduleId` (`ScheduleId`),
  KEY `FK_CitySchedules_Trains_TrainId` (`TrainId`),
  KEY `IX_CitySchedules_DepartureCityId` (`DepartureCityId`),
  KEY `IX_CitySchedules_DestinationCityId` (`DestinationCityId`),
  CONSTRAINT `FK_CitySchedules_Cities_DepartureCityId` FOREIGN KEY (`DepartureCityId`) REFERENCES `Cities` (`Id`) ON DELETE CASCADE,
  CONSTRAINT `FK_CitySchedules_Cities_DestinationCityId` FOREIGN KEY (`DestinationCityId`) REFERENCES `Cities` (`Id`) ON DELETE CASCADE,
  CONSTRAINT `FK_CitySchedules_Schedules_ScheduleId` FOREIGN KEY (`ScheduleId`) REFERENCES `Schedules` (`Id`) ON DELETE CASCADE,
  CONSTRAINT `FK_CitySchedules_Trains_TrainId` FOREIGN KEY (`TrainId`) REFERENCES `Trains` (`Id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1745513 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Customers`;

CREATE TABLE `Customers` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `PhoneNumber` varchar(20) CHARACTER SET utf8mb4 NOT NULL,
  `Email` varchar(100) CHARACTER SET utf8mb4 DEFAULT NULL,
  `UserId` int(11) NOT NULL,
  `AddressId` int(11) NOT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `IX_Customers_AddressId` (`AddressId`),
  UNIQUE KEY `IX_Customers_UserId` (`UserId`),
  CONSTRAINT `FK_Customers_Addresses_AddressId` FOREIGN KEY (`AddressId`) REFERENCES `Addresses` (`Id`) ON DELETE CASCADE,
  CONSTRAINT `FK_Customers_Users_UserId` FOREIGN KEY (`UserId`) REFERENCES `Users` (`Id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=71 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Logs`;

CREATE TABLE `Logs` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `OrderId` int(11) DEFAULT NULL,
  `CreatedOnUtc` datetime(6) NOT NULL,
  `OldValue` varchar(2000) CHARACTER SET utf8mb4 DEFAULT NULL,
  `NewValue` varchar(2000) CHARACTER SET utf8mb4 DEFAULT NULL,
  `ShortDescription` varchar(500) CHARACTER SET utf8mb4 DEFAULT NULL,
  `Description` longtext CHARACTER SET utf8mb4,
  `LogTypeName` varchar(100) CHARACTER SET utf8mb4 NOT NULL,
  PRIMARY KEY (`Id`),
  KEY `IX_Logs_LogTypeName` (`LogTypeName`),
  KEY `IX_Logs_OrderId` (`OrderId`),
  CONSTRAINT `FK_Logs_Orders_OrderId` FOREIGN KEY (`OrderId`) REFERENCES `Orders` (`Id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=20 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `OrderItems`;

CREATE TABLE `OrderItems` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Quantity` int(11) NOT NULL,
  `IsNew` tinyint(1) NOT NULL,
  `Description` longtext CHARACTER SET utf8mb4,
  `Price` decimal(12,2) NOT NULL DEFAULT '1.00',
  `OrderId` int(11) NOT NULL,
  PRIMARY KEY (`Id`),
  KEY `IX_OrderItems_OrderId` (`OrderId`),
  CONSTRAINT `FK_OrderItems_Orders_OrderId` FOREIGN KEY (`OrderId`) REFERENCES `Orders` (`Id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Orders`;

CREATE TABLE `Orders` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `CollectionDate` datetime NOT NULL,
  `EditDate` datetime(6) DEFAULT NULL,
  `Weight` double DEFAULT NULL,
  `Price` decimal(12,2) NOT NULL,
  `Height` double DEFAULT NULL,
  `Width` double DEFAULT NULL,
  `Length` double DEFAULT NULL,
  `DeclaredPrice` double DEFAULT NULL,
  `Status` int(11) NOT NULL DEFAULT '100',
  `StripeSessionId` varchar(255) CHARACTER SET utf8mb4 DEFAULT NULL,
  `PaymentStatus` int(11) NOT NULL DEFAULT '100',
  `PaymentMethod` int(11) NOT NULL DEFAULT '100',
  `PickupDate` datetime(6) DEFAULT NULL,
  `DispatchDate` datetime(6) NOT NULL,
  `ArrivalDate` datetime(6) NOT NULL,
  `ConductorPrice` decimal(65,30) NOT NULL DEFAULT '0.000000000000000000000000000000',
  `CityScheduleId` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`),
  KEY `IX_Orders_CityScheduleId` (`CityScheduleId`),
  CONSTRAINT `FK_Orders_CitySchedules_CityScheduleId` FOREIGN KEY (`CityScheduleId`) REFERENCES `CitySchedules` (`Id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `ParcelIdentifiers`;

CREATE TABLE `ParcelIdentifiers` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Guid` char(36) NOT NULL,
  `ParcelNumber` int(11) NOT NULL,
  `ParcelId` int(11) DEFAULT NULL,
  PRIMARY KEY (`Id`),
  UNIQUE KEY `IX_ParcelIdentifiers_ParcelId` (`ParcelId`),
  CONSTRAINT `FK_ParcelIdentifiers_Orders_ParcelId` FOREIGN KEY (`ParcelId`) REFERENCES `Orders` (`Id`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=32 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Roles`;

CREATE TABLE `Roles` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `UserRole` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Schedules`;

CREATE TABLE `Schedules` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `DateFrom` time(6) NOT NULL,
  `DateTo` time(6) NOT NULL,
  `Price` decimal(65,30) NOT NULL DEFAULT '79.000000000000000000000000000000',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=415954 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Settings`;

CREATE TABLE `Settings` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(200) CHARACTER SET utf8mb4 NOT NULL,
  `Value` varchar(400) CHARACTER SET utf8mb4 NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Trains`;

CREATE TABLE `Trains` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Type` varchar(32) CHARACTER SET utf8mb4 NOT NULL,
  `PKPId` int(11) NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=1344 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `UserOrders`;

CREATE TABLE `UserOrders` (
  `UserId` int(11) NOT NULL,
  `OrderId` int(11) NOT NULL,
  `Type` longtext CHARACTER SET utf8mb4,
  PRIMARY KEY (`OrderId`,`UserId`),
  KEY `IX_UserOrders_UserId` (`UserId`),
  CONSTRAINT `FK_UserOrders_Orders_OrderId` FOREIGN KEY (`OrderId`) REFERENCES `Orders` (`Id`) ON DELETE CASCADE,
  CONSTRAINT `FK_UserOrders_Users_UserId` FOREIGN KEY (`UserId`) REFERENCES `Users` (`Id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `UserRole`;

CREATE TABLE `UserRole` (
  `UserId` int(11) NOT NULL,
  `RoleId` int(11) NOT NULL,
  PRIMARY KEY (`RoleId`,`UserId`),
  KEY `IX_UserRole_UserId` (`UserId`),
  CONSTRAINT `FK_UserRole_Roles_RoleId` FOREIGN KEY (`RoleId`) REFERENCES `Roles` (`Id`) ON DELETE CASCADE,
  CONSTRAINT `FK_UserRole_Users_UserId` FOREIGN KEY (`UserId`) REFERENCES `Users` (`Id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `Users`;

CREATE TABLE `Users` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(40) CHARACTER SET utf8mb4 NOT NULL,
  `SurName` varchar(40) CHARACTER SET utf8mb4 NOT NULL,
  `UserName` varchar(40) CHARACTER SET utf8mb4 NOT NULL,
  `Password` varchar(40) CHARACTER SET utf8mb4 NOT NULL,
  `RefreshToken` varchar(128) CHARACTER SET utf8mb4 DEFAULT NULL,
  `TokenExpirationDate` datetime(6) DEFAULT NULL,
  `NIP` varchar(10) CHARACTER SET utf8mb4 DEFAULT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=72 DEFAULT CHARSET=utf8;
DROP TABLE IF EXISTS `__EFMigrationsHistory`;

CREATE TABLE `__EFMigrationsHistory` (
  `MigrationId` varchar(95) NOT NULL,
  `ProductVersion` varchar(32) NOT NULL,
  PRIMARY KEY (`MigrationId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;







































