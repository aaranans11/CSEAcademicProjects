----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01/30/2024 11:54:38 AM
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
-- SYSC3320 Lab 2: Testbench for Simple 2-to-4 Decoder component
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity testbench is
--  Port ( );
end testbench;

architecture Behavioral of testbench is
SIGNAL Inw0: STD_LOGIC:='0';
SIGNAL Inw1: STD_LOGIC:='0';
SIGNAL InEn: STD_LOGIC:='0';
SIGNAL Outy0: STD_LOGIC:='0';
SIGNAL Outy1: STD_LOGIC:='0';
SIGNAL Outy2: STD_LOGIC:='0';
SIGNAL Outy3: STD_LOGIC:='0';

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
    Dec_1 : Decoder_2_to_4
    port map(
        w0 => Inw0,
        w1 => Inw1,
        En => InEn,
        y0 => Outy0, 
        y1 => Outy1, 
        y2 => Outy2, 
        y3 => Outy3);
    
    process begin
        InEn <= '1';
       
        Inw0 <= '0';
        Inw1 <= '0';
        wait for 2 ns;
        
        Inw0 <= '0';
        Inw1 <= '1';
        wait for 2 ns;
        
        Inw0 <= '1';
        Inw1 <= '0';
        wait for 2 ns;
       
        Inw0 <= '1';
        Inw1 <= '1';
        wait for 2 ns;
        
        Inw0 <= '0';
        Inw1 <= '0';
        wait for 2 ns;
        
        InEn <= '0';
                
        Inw0 <= '0';
        Inw1 <= '0';
        wait for 2 ns;
        
        Inw0 <= '0';
        Inw1 <= '1';
        wait for 2 ns;
        
        Inw0 <= '1';
        Inw1 <= '0';
        wait for 2 ns;
       
        Inw0 <= '1';
        Inw1 <= '1';
        wait for 2 ns;
        
        Inw0 <= '0';
        Inw1 <= '0';
        wait for 2 ns;
        
    end process;

end Behavioral;
