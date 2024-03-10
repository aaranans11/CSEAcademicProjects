----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/30/2024 11:44:38 AM
-- Design Name: 
-- Module Name: Decoder_2_to_4 - Behavioral
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
-- SYSC3320 Lab 2: Simple 2-to-4 Decoder component
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Decoder_2_to_4 is
    Port ( w0 : in STD_LOGIC;
           w1 : in STD_LOGIC;
           En : in STD_LOGIC;
           y0 : out STD_LOGIC;
           y1 : out STD_LOGIC;
           y2 : out STD_LOGIC;
           y3 : out STD_LOGIC);
end Decoder_2_to_4;

architecture Behavioral of Decoder_2_to_4 is

begin

y0 <= En and (not w0) and (not w1);
y1 <= En and w0 and (not w1);
y2 <= En and (not w0) and w1;
y3 <= En and w0 and w1;

end Behavioral;
