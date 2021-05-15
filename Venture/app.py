from flask import Flask,render_template,request
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime


app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///Job_Storage.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)



class Job_Storage(db.Model):
    Company_name = db.Column(db.String(50),primary_key = True)
    Job_title = db.Column(db.String(50),primary_key = True)
    Job_email = db.Column(db.String(75),primary_key = True)
    Job_duration = db.Column(db.String(50),primary_key = True)
    # Job_starting_date = db.Column(db.DateTime, default=datetime.utcnow)
    Job_starting_date = db.Column(db.String(50),primary_key = True)
    Job_desc = db.Column(db.String(500),primary_key = True)
    Job_location = db.Column(db.String(500),primary_key = True)
    Job_skills_req = db.Column(db.String(500),primary_key = True)

    def __repr__(self) -> str:
        return f"{self.Company_name} - {self.Job_title}"

# def __init__(self, Company_name,Job_location ,Job_desc,Job_duration,Job_email,Job_title,Job_starting_date,Job_skills_req):
#     self.Company_name = Company_name
#     self.Job_title = Job_title
#     self.Job_duration = Job_duration
#     self.Job_starting_date = Job_starting_date
#     self.Job_desc = Job_desc
#     self.Job_location = Job_location
#     self.Job_skills_req = Job_skills_req



@app.route("/")
def index():
    return render_template("index.html")

@app.route("/dispAll")
def dispApp():
    
    return render_template("dispApp.html",allJobs = Job_Storage.query.all())

@app.route("/Job_entry", methods = ['GET','POST'])
def products():
    if request.method == 'POST':
        Job_Storage_e = Job_Storage(Company_name = request.form['Company_name'],Job_title = request.form['Job_title'],Job_email = request.form['Job_email'],Job_duration = request.form['Job_duration'],Job_starting_date=request.form['Job_starting_date'],Job_desc=request.form['Job_desc'],Job_location=request.form['Job_location'],Job_skills_req=request.form['Job_skills_req'])
        db.session.add(Job_Storage_e)
        db.session.commit()
    return render_template("JobInput.html")

if __name__ == "__main__":
    app.run(debug=True, port=2200)