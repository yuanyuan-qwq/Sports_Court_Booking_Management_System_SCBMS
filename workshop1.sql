-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 09, 2023 at 09:37 AM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.1.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `workshop1`
--

-- --------------------------------------------------------

--
-- Table structure for table `court_booking`
--

CREATE TABLE `court_booking` (
  `CourtBooking_ID` varchar(20) NOT NULL,
  `Customers_ID` varchar(20) NOT NULL,
  `SportCourt_ID` varchar(20) NOT NULL,
  `Staff_ID` varchar(20) NOT NULL,
  `DateIN` date NOT NULL,
  `DateOUT` date NOT NULL,
  `TotalDay` int(20) NOT NULL,
  `TotalCharge` float NOT NULL,
  `PaymentType` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `court_booking`
--

INSERT INTO `court_booking` (`CourtBooking_ID`, `Customers_ID`, `SportCourt_ID`, `Staff_ID`, `DateIN`, `DateOUT`, `TotalDay`, `TotalCharge`, `PaymentType`) VALUES
('B00000001', 'C00000001', 'SC00000002', 'S00000005', '2023-05-01', '2023-05-10', 9, 858.6, 'Online Banking'),
('B00000002', 'C00000001', 'SC00000002', 'S00000005', '2023-06-01', '2023-06-20', 19, 1631.34, 'Touch and Go'),
('B00000003', 'C00000003', 'SC00000001', 'S00000001', '2024-12-12', '2024-12-13', 1, 76.32, 'Cash'),
('B00000004', 'C00000004', 'SC00000002', 'S00000007', '2024-02-29', '2024-04-17', 48, 4579.2, 'Online Banking'),
('B00000005', 'C00000003', 'SC00000006', 'S00000002', '2023-03-15', '2023-03-30', 15, 2575.8, 'Touch and Go'),
('B00000006', 'C00000003', 'SC00000005', 'S00000005', '2023-06-01', '2023-06-10', 9, 954, 'Credit/Debit Card'),
('B00000007', 'C00000003', 'SC00000001', 'S00000001', '2023-04-15', '2023-04-25', 10, 848, 'Online Banking'),
('B00000008', 'C00000001', 'SC00000003', 'S00000006', '2023-02-01', '2023-02-20', 19, 4028, 'Cash'),
('B00000009', 'C00000005', 'SC00000005', 'S00000004', '2023-07-01', '2023-07-15', 14, 1335.6, 'Credit/Debit Card'),
('B00000010', 'C00000005', 'SC00000002', 'S00000007', '2023-08-01', '2023-08-10', 9, 772.74, 'Credit/Debit Card'),
('B00000011', 'C00000006', 'SC00000001', 'S00000001', '2023-09-11', '2023-09-30', 19, 1611.2, 'Credit/Debit Card'),
('B00000012', 'C00000001', 'SC00000002', 'S00000008', '2023-01-01', '2023-01-15', 14, 1202.04, 'Credit/Debit Card'),
('B00000013', 'C00000006', 'SC00000002', 'S00000008', '2023-11-01', '2023-11-15', 14, 1335.6, 'Credit/Debit Card'),
('B00000014', 'C00000008', 'SC00000001', 'S00000001', '2023-12-01', '2023-12-15', 14, 1068.48, 'Cash'),
('B00000015', 'C00000009', 'SC00000004', 'S00000003', '2023-04-20', '2023-04-30', 10, 1144.8, 'Touch and Go'),
('B00000016', 'C00000009', 'SC00000003', 'S00000006', '2023-10-25', '2023-11-10', 16, 3052.8, 'Credit/Debit Card'),
('B00000017', 'C00000010', 'SC00000004', 'S00000003', '2023-05-05', '2023-05-30', 25, 3180, 'Online Banking'),
('B00000018', 'C00000010', 'SC00000004', 'S00000005', '2023-07-01', '2023-07-20', 19, 2416.8, 'Credit/Debit Card'),
('B00000019', 'C00000010', 'SC00000004', 'S00000003', '2023-12-15', '2023-12-30', 15, 1717.2, 'Credit/Debit Card'),
('B00000020', 'C00000010', 'SC00000004', 'S00000003', '2023-11-10', '2023-11-30', 20, 2544, 'Online Banking'),
('B00000021', 'C00000010', 'SC00000004', 'S00000003', '2023-08-01', '2023-08-15', 14, 1780.8, 'Touch and Go'),
('B00000022', 'C00000010', 'SC00000004', 'S00000003', '2023-09-15', '2023-09-30', 15, 1908, 'Credit/Debit Card'),
('B00000023', 'C00000003', 'SC00000006', 'S00000002', '2023-08-15', '2023-08-30', 15, 2862, 'Credit/Debit Card'),
('B00000024', 'C00000012', 'SC00000002', 'S00000008', '2023-10-11', '2023-10-30', 19, 1812.6, 'Online Banking'),
('B00000026', 'C00000001', 'SC00000001', 'S00000001', '2023-11-05', '2023-11-06', 1, 84.8, 'Online Banking'),
('B00000027', 'C00000011', 'SC00000007', 'S00000005', '2023-10-01', '2023-10-25', 24, 1526.4, 'Credit/Debit Card'),
('B00000028', 'C00000013', 'SC00000007', 'S00000005', '2023-04-25', '2023-04-28', 3, 190.8, 'Cash'),
('B00000029', 'C00000001', 'SC00000007', 'S00000005', '2023-04-29', '2023-04-30', 1, 63.6, 'Touch and Go'),
('B00000030', 'C00000014', 'SC00000007', 'S00000005', '2023-11-10', '2023-11-11', 1, 57.24, 'Cash'),
('B00000031', 'C00000015', 'SC00000004', 'S00000003', '2023-11-01', '2023-11-02', 1, 114.48, 'Online Banking'),
('B00000032', 'C00000011', 'SC00000006', 'S00000002', '2024-01-01', '2024-01-25', 24, 4121.28, 'Credit/Debit Card'),
('B00000033', 'C00000011', 'SC00000007', 'S00000005', '2024-11-10', '2024-11-30', 20, 1272, 'Online Banking'),
('B00000034', 'C00000011', 'SC00000005', 'S00000004', '2023-10-01', '2023-10-25', 24, 2544, 'Credit/Debit Card'),
('B00000035', 'C00000016', 'SC00000001', 'S00000001', '2023-05-16', '2023-05-20', 4, 305.28, 'Cash'),
('B00000036', 'C00000017', 'SC00000005', 'S00000004', '2024-05-31', '2024-06-02', 2, 212, 'Touch and Go');

-- --------------------------------------------------------

--
-- Table structure for table `customers`
--

CREATE TABLE `customers` (
  `Customers_ID` varchar(20) NOT NULL,
  `C_Name` varchar(50) NOT NULL,
  `C_Type` varchar(50) NOT NULL,
  `C_Address` varchar(100) DEFAULT NULL,
  `C_HpNo` varchar(12) NOT NULL,
  `C_Email` varchar(50) NOT NULL,
  `password` varchar(20) NOT NULL,
  `status` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `customers`
--

INSERT INTO `customers` (`Customers_ID`, `C_Name`, `C_Type`, `C_Address`, `C_HpNo`, `C_Email`, `password`, `status`) VALUES
('C00000001', 'yuan', 'Individual', 'Raub', '010-3352070', 'yuan@utem.com', 'yuan', 'Active'),
('C00000003', 'DR.Andrew', 'Organization', 'New York', '013-5678431', 'start@gg.com', 'DR.andrew', 'Active'),
('C00000004', 'Bibi chong', 'Individual', 'Raub Durian king', '016-8888888', 'bibichong@mei.cpn', 'bibi chong', 'Frozen'),
('C00000005', 'lance', 'Individual', 'Pahang Raub cheloh', '013-6794538', 'lance@lc.com', 'lance', 'Active'),
('C00000006', 'wei kang', 'Individual', 'taiping', '013-4546369', 'weikang@utem.com', 'wei kang', 'Active'),
('C00000008', 'hoe wai', 'Individual', 'asfhjsdjfhj', '010-12663843', 'qwer@utem.edu', 'ww', 'Active'),
('C00000009', 'pang yee xuan', 'Individual', 'melaka', '010-3262105', 'yeexuan@queen.com', 'pang yee xuan', 'Active'),
('C00000010', 'Dato lee chong wei', 'Organization', 'kuala lumpur', '010-19821021', 'LeeChongWei@official.my', 'dato', 'Active'),
('C00000011', 'qin tong', 'Organization', 'sabah', '010-1152340', 'qintong@biubiu.com', 'qin tong', 'Active'),
('C00000012', 'company NBA', 'Organization', 'US', '013-1265421', 'wakawaka@NBA.my', 'nba', 'Active'),
('C00000013', 'jun kent', 'Individual', 'johor', '010-3362160', 'rick@rock.com', 'jun kent', 'Active'),
('C00000014', 'xiao', 'Individual', 'liyue', '010-3352070', 'xiao@genshin.my', 'xiao', 'Active'),
('C00000015', 'bibi', 'Individual', 'raub', '010-2236528', 'bibi@gg.com', 'bibi', 'Active'),
('C00000016', 'yuanyuan', 'Individual', 'ruab', '010-3352070', 'yuan@utem.com', 'yuan1', 'Active'),
('C00000017', 'lai chun wai', 'Individual', 'raub', '010-4432170', 'lai0531@gmail.com', 'lcw', 'Active');

-- --------------------------------------------------------

--
-- Table structure for table `manager`
--

CREATE TABLE `manager` (
  `Manager_ID` varchar(20) NOT NULL,
  `M_Name` varchar(50) NOT NULL,
  `M_Gender` varchar(15) DEFAULT NULL,
  `M_HpNo` varchar(12) NOT NULL,
  `M_Email` varchar(50) DEFAULT NULL,
  `password` varchar(20) NOT NULL,
  `status` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `manager`
--

INSERT INTO `manager` (`Manager_ID`, `M_Name`, `M_Gender`, `M_HpNo`, `M_Email`, `password`, `status`) VALUES
('M00000001', 'yuan', 'Male', '010-3352070', 'yuan@utem.com', 'yuan', 'Active'),
('M00000002', '1', 'Male', '1', '1@.1', '1', 'Active');

-- --------------------------------------------------------

--
-- Table structure for table `sport_court`
--

CREATE TABLE `sport_court` (
  `SportCourt_ID` varchar(20) NOT NULL,
  `SC_Name` varchar(50) NOT NULL,
  `SC_Status` varchar(20) NOT NULL,
  `PricePerDay` float NOT NULL,
  `Staff_ID` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `sport_court`
--

INSERT INTO `sport_court` (`SportCourt_ID`, `SC_Name`, `SC_Status`, `PricePerDay`, `Staff_ID`) VALUES
('SC00000001', 'Football Court', 'AVAILABLE', 80, 'S00000001'),
('SC00000002', 'Basketball Court', 'MAINTENANCE', 90, 'S00000008'),
('SC00000003', 'Swimming Pool', 'AVAILABLE', 200, 'S00000006'),
('SC00000004', 'Badminton Court', 'AVAILABLE', 120, 'S00000003'),
('SC00000005', 'Skatepark', 'AVAILABLE', 100, 'S00000004'),
('SC00000006', 'Gymnasiums', 'AVAILABLE', 180, 'S00000002'),
('SC00000007', 'Volleyball Court', 'AVAILABLE', 60, 'S00000005');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `Staff_ID` varchar(20) NOT NULL,
  `Manager_ID` varchar(20) NOT NULL,
  `S_Name` varchar(50) NOT NULL,
  `S_Gender` varchar(20) DEFAULT NULL,
  `S_HpNo` varchar(12) NOT NULL,
  `S_Email` varchar(50) DEFAULT NULL,
  `password` varchar(20) NOT NULL,
  `status` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`Staff_ID`, `Manager_ID`, `S_Name`, `S_Gender`, `S_HpNo`, `S_Email`, `password`, `status`) VALUES
('S00000001', 'M00000001', 'ang wei kang', 'Other', '012-1234563', 'weikang@wk.com', 'angweikang', 'Active'),
('S00000002', 'M00000001', 'sim weng jin', 'Male', '014-1264536', 'wenjing@sim.com', 'sim', 'Active'),
('S00000003', 'M00000001', 'teh xiao thong', 'Female', '010-5543267', 'xiao@txt.com', 'txt', 'Active'),
('S00000004', 'M00000001', 'lai chun wai', 'Female', '010-4463213', 'lance@gmail.com', 'lcw', 'Active'),
('S00000005', 'M00000001', 'andrew', 'Male', '014-4123142', 'andrew@yuan.com', 'andrew', 'Active'),
('S00000006', 'M00000001', 'tan zi bin', 'Male', '013-1468293', 'zibin@yyds.com', 'zb', 'Active'),
('S00000007', 'M00000001', 'Darrick', 'Male', '010-2253170', 'hengOng@huat.com', 'd', 'Active'),
('S00000008', 'M00000001', 'yuan', 'Male', '010-3352070', 'fuyuanlum@gmail.com', 'yuan', 'Active'),
('S00000009', 'M00000001', 'weikang123', 'Male', '012-7786532', 'wk@utem.com', 'wk', 'Frozen');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `court_booking`
--
ALTER TABLE `court_booking`
  ADD PRIMARY KEY (`CourtBooking_ID`),
  ADD KEY `Customers_ID` (`Customers_ID`),
  ADD KEY `SportCourt_ID` (`SportCourt_ID`),
  ADD KEY `Staff_ID` (`Staff_ID`);

--
-- Indexes for table `customers`
--
ALTER TABLE `customers`
  ADD PRIMARY KEY (`Customers_ID`),
  ADD UNIQUE KEY `C_Name` (`C_Name`);

--
-- Indexes for table `manager`
--
ALTER TABLE `manager`
  ADD PRIMARY KEY (`Manager_ID`),
  ADD UNIQUE KEY `M_Name` (`M_Name`);

--
-- Indexes for table `sport_court`
--
ALTER TABLE `sport_court`
  ADD PRIMARY KEY (`SportCourt_ID`),
  ADD UNIQUE KEY `SC_Name` (`SC_Name`),
  ADD KEY `Staff_ID` (`Staff_ID`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`Staff_ID`),
  ADD UNIQUE KEY `S_Name` (`S_Name`),
  ADD KEY `Manager_ID` (`Manager_ID`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `court_booking`
--
ALTER TABLE `court_booking`
  ADD CONSTRAINT `court_booking_ibfk_1` FOREIGN KEY (`Customers_ID`) REFERENCES `customers` (`Customers_ID`),
  ADD CONSTRAINT `court_booking_ibfk_2` FOREIGN KEY (`SportCourt_ID`) REFERENCES `sport_court` (`SportCourt_ID`),
  ADD CONSTRAINT `court_booking_ibfk_3` FOREIGN KEY (`Staff_ID`) REFERENCES `staff` (`Staff_ID`);

--
-- Constraints for table `sport_court`
--
ALTER TABLE `sport_court`
  ADD CONSTRAINT `sport_court_ibfk_1` FOREIGN KEY (`Staff_ID`) REFERENCES `staff` (`Staff_ID`);

--
-- Constraints for table `staff`
--
ALTER TABLE `staff`
  ADD CONSTRAINT `Manager_ID` FOREIGN KEY (`Manager_ID`) REFERENCES `manager` (`Manager_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
