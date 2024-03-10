----------------------------------------------------------------------------------
-- SYSC3320 Lab 3
-- Aaranan Sathiendran
-- 101196339
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_signed.all;

entity ALU is
    port (
        op : in std_logic_vector(2 downto 0);
        -- a, b : in std_logic_vector(7 downto 0);
        result : out std_logic_vector(3 downto 0)
    );
end ALU;

architecture Behavioral of ALU is
signal a: std_logic_vector(3 downto 0):= "1100" ;
signal b: std_logic_vector(3 downto 0):= "1001" ;
signal res: std_logic_vector(3 downto 0) ;
begin
    process(op, a, b)
    begin
        case op is
            when "000" =>  -- Addition
                res <= a+b;
            -- Subtraction
            when "001" =>
                res <= a - b;
            -- Logical AND
           when "010" =>
                res <= a AND b;
             -- Logical OR
           when "011" =>
                res <= a OR b;
           when "100" =>
                res <= a XOR b;
           when "101" =>
                res <= a XNOR b;
           when others =>
                res <= "0000";
        end case;

      result <=res;
    end process;
end Behavioral;
