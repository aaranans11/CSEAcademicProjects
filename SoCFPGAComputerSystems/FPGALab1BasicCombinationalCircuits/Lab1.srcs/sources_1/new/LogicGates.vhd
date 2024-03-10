----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/16/2024 02:51:29 PM
-- Design Name: 
-- Module Name: LogicGates - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
-- Aaranan Sathiendran
-- 101196339
-- SYSC3320 Lab 1: Combinational Circuit
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity LogicGates is
    Port ( A : in STD_LOGIC;
           B : in STD_LOGIC;
           Z : out STD_LOGIC_VECTOR (3 downto 0));
end LogicGates;

architecture Behavioral of LogicGates is

begin
 Z(0)<= A and B;
 Z(1)<= A or B;
 Z(2)<= A xor B;
 Z(3)<= A nor B;


end Behavioral;
