----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/30/2024 01:27:21 PM
-- Design Name: 
-- Module Name: Top_Decoder_2_to_4 - Behavioral
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
-- SYSC3320 Lab 2: Top level design for Simple 2-to-4 Decoder component
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Top_Decoder_2_to_4 is
    Port ( btn : in STD_LOGIC_VECTOR (3 downto 0);
           sw : in STD_LOGIC_VECTOR (3 downto 0);
           led : out STD_LOGIC_VECTOR (3 downto 0));
end Top_Decoder_2_to_4;

architecture Behavioral of Top_Decoder_2_to_4 is

component Decoder_2_to_4 is
    Port( w0 : in STD_LOGIC;
          w1 : in STD_LOGIC;
          En : in STD_LOGIC;
          y0 : out STD_LOGIC;
          y1 : out STD_LOGIC;
          y2 : out STD_LOGIC;
          y3 : out STD_LOGIC);
end component;

begin

    D1 : Decoder_2_to_4
    port map(
        w0 => btn(0),
        w1 => btn(1),
        En => sw(0),
        y0 => led(0),
        y1 => led(1),
        y2 => led(2),
        y3 => led(3));

end Behavioral;
