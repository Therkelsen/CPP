  #include "database.h"

  Database::Database()
    :db() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Traade_og_DB/bil_db.db");

    db.open();

    if (!db.open()){
        std::cout << "\nDB: Failed to load database" << std::endl;
      } else {
        std::cout << "\nDB: Database loaded" << std::endl;
        QSqlQuery query("CREATE TABLE IF NOT EXISTS bil (bil_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, registreringsnr char(7) NOT NULL, model char(20) NOT NULL, aargang NOT NULL)");
        if (!query.exec()) {
          std::cout << "\nDB: Table could not be created" << std::endl;
        }
        query.prepare("INSERT INTO tasks (taskId) VALUES (:id)");
      }
  }

  void Database::extractData() {
    entries = 0;
    QSqlQuery query;
    std::cout << "\nDB: All currently existing rows:" << std::endl;
    query.exec("SELECT * FROM bil");
    while(query.next()) {
      entries++;
      int bil_id = query.value(0).toInt();
      QString regnumm = query.value(1).toString(); std::string regnr = regnumm.toUtf8().constData();
      QString mod = query.value(2).toString(); std::string model = mod.toUtf8().constData();
      int aargang = query.value(3).toInt();
      std::cout << "bil_id: " << std::setw(6) << std::left << bil_id << " | regnr: " << regnr;
      std::cout << " | model: " << std::setw(19) << std::left << model << " | aargang: " << aargang << std::endl;
    }
  }

  std::string Database::extractHighestRegNr() {
    QSqlQuery query;
    std::string regnr;
    query.exec("SELECT registreringsnr FROM bil ORDER BY registreringsnr desc limit 1");
    std::cout << std::endl;
    while(query.next()) {
      QString regnumm = query.value(0).toString(); regnr = regnumm.toUtf8().constData();
    }
    if(query.exec()) {
      std::cout << "DB: Highest regnr: " << regnr << std::endl;
    }
    return regnr;
  }

  void Database::insertData(QString regnr, QString model, int aar) {
    countEntries();
    QSqlQuery query;
    query.prepare("SELECT EXISTS(SELECT 1 FROM bil WHERE registreringsnr = :regnr)");
    query.bindValue(":regnr", regnr);
    query.exec();
    bool exists = false;
    while(query.next()) {
        if (query.value(0) == 1) {
            exists = true;
        }
    }
    if (!exists) {
        std::cout << "\nDB: Inserting data to database:" << std::endl;
        QSqlQuery query;
        query.prepare("INSERT INTO bil (registreringsnr, model, aargang) "
                      "VALUES (:registreringsnr, :model, :aargang)");

        query.bindValue(":registreringsnr", regnr);
        query.bindValue(":model", model);
        query.bindValue(":aargang", aar);
        query.exec();
    } else {
        std::cout << "\nDB: regNr already exists, updating data" << std::endl;
        QSqlQuery query;
        query.prepare("UPDATE bil SET model = :model, aargang = :aargang "
                      "WHERE registreringsnr = :registreringsnr");

        query.bindValue(":registreringsnr", regnr);
        query.bindValue(":model", model);
        query.bindValue(":aargang", aar);
        query.exec();
    }
  }

  unsigned int Database::countEntries() {
    entries = 0;
    QSqlQuery query;
    query.exec("SELECT * FROM bil");
    while(query.next()) {
        entries++;
    }
    return entries;
  }

  void Database::clearDatabase() {
    QSqlQuery query;
    query.prepare("DROP TABLE bil");
    if(!query.exec()) {
       qDebug() << query.lastError();
    } else {
       qDebug("\nDB: Data cleared" );
    }
    countEntries();
  }

  void Database::disconnect() {
    std::cout << "\nDB: Disconnecting from database" << std::endl;
    db.close();
  }
