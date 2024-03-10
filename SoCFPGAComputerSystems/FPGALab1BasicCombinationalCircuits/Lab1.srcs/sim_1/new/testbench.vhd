----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/16/2024 03:11:31 PM
-- Design Name: 
-- Module Name: testbench - Behavioral
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
-- Aaranan Sathiendran 101196339
-- SYSC3320 Lab 1: Combinational Circuit
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity testbench is
--  Port ( );
end testbench;

architecture Behavioral of testbench is

SIGNAL InA : STD_LOGIC :='0';
SIGNAL InB : STD_LOGIC :='0';
SIGNAL OutZ : STD_LOGIC_VECTOR (3 downto 0) := "0000";

component LogicGates is
    Port( A : in STD_LOGIC;
          B : in STD_LOGIC;
          Z : out STD_LOGIC_VECTOR (3 downto 0));
end component;

begin

    LG1 : LogicGates
    port map(
        A => InA,
        B => InB,
        Z(0) => OutZ(0),
        Z(1) => OutZ(1),
        Z(2) => OutZ(2),
        Z(3) => OutZ(3));
        
    process begin
        InA <= '0';
        InB <= '0';
        wait for 2 ns;
        InA <= '1';
        wait for 2 ns;
        InA <= '0';
        wait for 2 ns;
        InB <= '1';
        wait for 2 ns;
        InB <= '0';
        wait for 2 ns;
    end process;

end Behavioral;