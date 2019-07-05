#include "usernamelib.h"
namespace UserNameLib {
QString getUserName(void){
    if(UserNameLib::userName==""){
        FileReader fr(QCoreApplication::applicationDirPath()+"\\data.json");
        QJsonObject jobj=fr.getJson();
        QString name;
        if(jobj.contains("name")){
            name=jobj.value("name").toString();
        }else{
            qDebug()<<"JSON文件遭到损坏：无法找到name";
            exit(0);
        }
        UserNameLib::userName=name;
        return name;
    }
    else{
        return UserNameLib::userName;
    }
}

}
