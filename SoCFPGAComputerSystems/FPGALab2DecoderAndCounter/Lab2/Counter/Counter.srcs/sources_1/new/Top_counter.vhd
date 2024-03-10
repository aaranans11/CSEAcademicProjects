----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/30/2024 02:46:24 PM
-- Design Name: 
-- Module Name: Top_counter - Behavioral
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
-- SYSC3320 Lab 2: Top level for 4 bit up counter design 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Top_counter is
    Port ( btn : in STD_LOGIC_VECTOR (3 downto 0);
           led : out STD_LOGIC_VECTOR (3 downto 0));
end Top_counter;

architecture Behavioral of Top_counter is
component Counter_design1 is
    Port (clock : in STD_LOGIC;
          reset : in STD_LOGIC;
          count : out STD_LOGIC_VECTOR (3 downto 0));
end component;

component Counter_design2 is
    Port (clock : in STD_LOGIC;
          reset : in STD_LOGIC;
          count : out STD_LOGIC_VECTOR (3 downto 0));
end component;

begin
    C1: Counter_design1 port map(clock => btn(0), reset => btn(1), count => led);
    C2: Counter_design2 port map(clock => btn(0), reset => btn(1), count => led);

end Behavioral;
