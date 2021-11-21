CREATE TABLE bil (bil_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, registreringsnr char(7) NOT NULL, model char(20) NOT NULL, aargang NOT NULL);

CREATE INDEX bil_idx ON bil (bil_id, registreringsnr, model, aargang);
CREATE INDEX bil_idx ON bil (registreringsnr);