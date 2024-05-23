const express = require("express");
const bodyParse = require("body-parser");
const sqlite3 = require("sqlite3").verbose();
const PORT = 3000;

const app = express();
app.use(bodyParse.json());

app.post("/salvar-percurso", (req,res) =>
{
    
    const {id,acao,inicio_ms,fim_ms} = req.body;
    const db = new sqlite3.Database('./viagem.db');
    const sql = `INSERT INTO viagem(id,acao,inicio_ms,fim_ms) VALUES (?,?,?)`;

    db.run(sql, [id,acao,inicio_ms,fim_ms], function(err){
        if(err)
        {
            console.log(err.message);
            res.status(500).send("Erro ao salvar o arquivo");
        }
        else
        {
            console.log("Dados sendo salvo");
        }
        db.close();
        res.send("Arquivo salvo com sucesso!");
    });
    db.close();
}).listen(PORT,() =>
{
    console.log(`Porta de utilização é ${PORT}`);
});