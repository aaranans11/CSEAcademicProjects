----------------------------------------------------------------------------------
-- SYSC3320 Lab 3
-- Aaranan Sathiendran
-- 101196339
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_signed.all;

entity alu_tb is
end alu_tb;

architecture Behavioral of alu_tb is
  component alu is
    port (
      op : in std_logic_vector(1 downto 0);
      a, b : in std_logic_vector(3 downto 0);
      result : out std_logic_vector(3 downto 0)
    );
  end component;

  signal op : std_logic_vector(1 downto 0);
  signal a, b, result : std_logic_vector(3 downto 0);

begin

  dut : alu port map (
    op => op,
    a => a,
    b => b,
    result => result
  );
  process begin
      -- Test addition operation
      op <= "00";
      a <= "1100";
      b <= "1001";
      -- output should be 00010101
      wait for 10 ns;
    
      -- Test subtraction operation
       op <= "01";
       a <= "1100";
       b <= "1001";
       -- output should be 00000011
       wait for 10 ns;
    
    ---------------------------
      -- Test logical AND operation
       op <= "10";
       a <= "1100";
       b <= "1001";
       -- output should be 00001000
       wait for 10 ns;
    
      -- Test logical OR operation
       op <= "11";
       a <= "1100";
       b <= "1001";
       -- output should be 00001101
       wait for 10 ns;
   end process;

end Behavioral;
