LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY blink IS
   PORT(rst:  IN  std_logic;  -- reset, low active
        clk:  IN  std_logic;  -- clock, rising edge active
        led:  OUT std_logic); -- led, high active
END blink;

ARCHITECTURE verhalten OF blink IS
   
   CONSTANT RSTDEF: std_logic := '0';
   CONSTANT SYSFRQ: real      := 100.0e6;
   CONSTANT LEDFRQ: real      := 1.0;
   CONSTANT CNTMAX: natural   := natural(SYSFRQ/LEDFRQ);
   
   SIGNAL cnt: integer RANGE 0 TO CNTMAX-1;
   
BEGIN

   p1: PROCESS (rst, clk) IS
   BEGIN
      IF rst=RSTDEF THEN
         cnt <= 0;
         led <= '0';
      ELSIF rising_edge(clk) THEN
         cnt <= (cnt + 1) MOD CNTMAX;
         IF cnt=CNTMAX/2-1 THEN
            led <= '1';
         ELSIF cnt=CNTMAX-1 THEN
            led <= '0';
         END IF;
      END IF;
   END PROCESS;

END verhalten;