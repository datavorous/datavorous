from flask import Flask, render_template, request, redirect, url_for, flash
import json
from datetime import datetime

app = Flask(__name__)
app.secret_key = 'your_secret_key_here'  # Required for flash messages

DATA_FILE = 'question_data.json'

def load_data():
    try:
        with open(DATA_FILE, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        return {"users": {}}

def save_data(data):
    with open(DATA_FILE, 'w') as f:
        json.dump(data, f, indent=2)

@app.template_filter('enumerate')
def enumerate_filter(sequence, start=0):
    return enumerate(sequence, start=start)

@app.route('/')
def index():
    data = load_data()
    sorted_users = sorted(data['users'].items(), key=lambda x: x[1]['total_questions'], reverse=True)
    return render_template('index.html', users=sorted_users)

@app.route('/create_account', methods=['POST'])
def create_account():
    data = load_data()
    username = request.form['new_username']
    if username in data['users']:
        flash(f'Username {username} already exists.', 'error')
    else:
        data['users'][username] = {"total_questions": 0, "last_updated": ""}
        save_data(data)
        flash(f'Account created for {username}.', 'success')
    return redirect(url_for('index'))

@app.route('/log_questions', methods=['POST'])
def log_questions():
    data = load_data()
    username = request.form['username']
    questions = int(request.form['questions'])
    
    if username not in data['users']:
        flash(f'User {username} does not exist.', 'error')
    else:
        data['users'][username]['total_questions'] += questions
        data['users'][username]['last_updated'] = datetime.now().strftime("%d/%m/%Y")
        save_data(data)
        flash(f'Logged {questions} questions for {username}.', 'success')
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)
