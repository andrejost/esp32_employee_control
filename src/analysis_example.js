
'use strict';
const Analysis = require('tago/analysis');
const Utils    = require('tago/utils');
const Device   = require('tago/device');
 
function run_analysis(context) {
 
    //Recupera as variáveis de ambiente
    const env_vars  = Utils.env_to_obj(context.environment);
 
    //Cria um tipo Device utilizando a variável de ambiente DEVICE_TOKEN
    const my_device = new Device(env_vars.device_token);
     
    //No dispositivo, procura a variável e retorna o último item.
    my_device.find({"variable":"rfid_tag", "query":"last_item"}).then((result_array) => {
        if (!result_array[0]) {
            return context.log("Não encontrei nada no device");
        }
        
        //Valor da variável recebida
        const value = result_array[0].value;
 
        //Cria um novo dicionário utilizando a variável semaforo
        if (result_array[0].value == "Cartao 1: RFID CARD 1 ID"){
              const obj_to_save = {
                  "variable": "nome_empregado",
                  "value": ("Julio")
              };
              context.log(obj_to_save);
              //Insere dados da variável semaforo no dispositivo
              my_device.insert(obj_to_save).then(context.log("Ok, funcionou")).catch(error => context.log("Erro ao inserir", error));
        }
        if (result_array[0].value == "Cartao 2: RFID CARD 2 ID"){
              const obj_to_save = {
                  "variable": "nome_empregado",
                  "value": ("Maria")
              };
              context.log(obj_to_save);
              //Insere dados da variável semaforo no dispositivo
              my_device.insert(obj_to_save).then(context.log("Ok, funcionou")).catch(error => context.log("Erro ao inserir", error));
        } 
        
      }).catch(context.log);

}
module.exports = new Analysis(run_analysis, 'REPLACE HERE WITH THE ID OF YOUR ANALYSIS');