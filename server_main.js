const express = require("express");
const bodyParse = require("body-parser");
const sqlite3 = require("sqlite3").verbose();
const PORT = 3000;

const app = express();
app.use(bodyParse.json());

app.post("/salvar-percurso", (req,res) =>
{
    const {user_id,data_hora,local_id} = req.body;
    const db = new sqlite3.Database('./carro.db');

    db.run(`INSERT INTO Percursos (usuario_id, data_hora, local_id) VALUES (?,?,?)`,
    [user_id,data_hora,local_id],function(err){
        if(err)
            {
                console.log(err.message);
            }
        else
        console.log("Dados sendo salvo");
            db.close();
            res.send("Arquivo salvo com sucesso!");
    });
    db.close();
}).listen(PORT,() =>
{
    console.log(`Porta de utilização é ${PORT}`);
});