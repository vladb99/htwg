create view chefsA(chef) as
select name
from pers
connect by pnr = PRIOR vnr
start with pnr =
	(select vnr from pers where name = 'Abel');

create view chefsJ(chef) as
select name
from pers
connect by pnr = PRIOR vnr
start with pnr =
	(select vnr from pers where name = 'Junghans');

select distinct A.chef
from chefsA A, chefsJ J
where A.chef = J.chef;