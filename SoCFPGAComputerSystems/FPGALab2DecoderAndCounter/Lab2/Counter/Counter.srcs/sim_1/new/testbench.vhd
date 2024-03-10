----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/30/2024 02:13:55 PM
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
-- Aaranan Sathiendran
-- 101196339
-- SYSC3320 Lab 2: testbench for 4 bit up counter design 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity testbench is
--  Port ( );
end testbench;

architecture Behavioral of testbench is
    signal Inclock: std_logic :='0';
    signal Inreset: std_logic :='0';
    signal Outcount1: std_logic_vector (3 downto 0);
    signal Outcount2: std_logic_vector (3 downto 0);
    
component Counter_design1 is
    Port ( clock : in STD_LOGIC;
           reset : in STD_LOGIC;
           count : out STD_LOGIC_VECTOR (3 downto 0));
end component;

component Counter_design2 is
    Port ( clock : in STD_LOGIC;
           reset : in STD_LOGIC;
           count : out STD_LOGIC_VECTOR (3 downto 0));
end component;

begin
    C1: Counter_design1 port map(clock => Inclock, reset => Inreset, count => Outcount1);
    C2: Counter_design2 port map(clock => Inclock, reset => Inreset, count => Outcount2);
    
    process begin
        Inreset <= '1';
        Inclock <= '0';
        wait for 2 ns;
        Inclock <= '1';
        wait for 2ns;
        Inreset <= '0';
        Inclock <= '0';
        wait for 2 ns;
        
        for l in 0 to 15 loop
            Inclock <= '1';
            wait for 2ns;
            Inclock <= '0';
            wait for 2 ns;
        end loop;
    end process;

end Behavioral;
