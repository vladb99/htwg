
ENTITY blink2 IS
   PORT(LED: OUT BIT);
END blink2;

ARCHITECTURE verhalten OF blink2 IS
BEGIN
   
   PROCESS BEGIN
      LOOP
         LED <= '0';
         WAIT FOR 500 ms;
         LED <= '1';
         WAIT FOR 500 ms;
      END LOOP;
   END PROCESS;

END verhalten;