  #include "database.h"

  Database::Database()
    :db() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Traade_og_DB/bil_db.db");

    db.open();

    if (!db.open()){
        std::cout << "DB: Failed to load database" << std::endl;
      } else {
        std::cout << "DB: Database loaded" << std::endl;
        QSqlQuery query("CREATE TABLE IF NOT EXISTS bil (bil_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, registreringsnr char(7) NOT NULL, model char(20) NOT NULL, aargang NOT NULL)");
        if (!query.exec()) {
          std::cout << "DB: Table could not be created" << std::endl;
        }
        query.prepare("INSERT INTO tasks (taskId) VALUES (:id)");
      }
  }

  void Database::extractData() {
    entries = 0;
    QSqlQuery query;
    query.exec("SELECT * FROM bil");
    std::cout << std::endl;
    while(query.next()) {
      entries++;
      int bil_id = query.value(0).toInt();
      QString regnumm = query.value(1).toString(); std::string regnr = regnumm.toUtf8().constData();
      QString mod = query.value(2).toString(); std::string model = mod.toUtf8().constData();
      int aargang = query.value(3).toInt();
      std::cout << "DB: bil_id: " << bil_id << " | regnr: " << regnr;
      std::cout << " | model: " << model << " | aargang: " << aargang << std::endl;
    }
  }

  void Database::insertData(QString regnr, QString model, int aar) {
    countEntries();
    std::cout << "\nDB: Inserting data to database" << std::endl;
    QSqlQuery query;
    query.prepare("INSERT INTO bil (registreringsnr, model, aargang) "
                  "VALUES (:registreringsnr, :model, :aargang)");

    query.bindValue(":registreringsnr", regnr);
    query.bindValue(":model", model);
    query.bindValue(":aargang", aar);
    query.exec();
    entries++;
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
    std::cout << "DB: Disconnecting from database" << std::endl;
    db.close();
  }
