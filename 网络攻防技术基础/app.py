from flask import Flask, request, render_template_string
import mysql.connector

app = Flask(__name__)

# 数据库配置，请根据实际情况替换以下字段
db_config = {
    'user': 'root',
    'password': 'renyu20031205.',
    'host': 'localhost',
    'database': 'test_users',
}

@app.route('/')
def home():
    return '''
    <html>
        <body>
            <form action="/login" method="post">
                <label for="username">Username:</label><br>
                <input type="text" id="username" name="username"><br>
                <label for="password">Password:</label><br>
                <input type="password" id="password" name="password"><br><br>
                <input type="submit" value="Login">
            </form> 
        </body>
    </html>
    '''

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    try:
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()
        query = f"SELECT * FROM users WHERE username = '{username}' AND password = '{password}'"
        cursor.execute(query)
        user = cursor.fetchone()
    except mysql.connector.Error as err:
        response = "Error occurred: " + str(err)
    else:
        if user:
            response = "Login successful!"
        else:
            response = "Login failed!"
    finally:
        cursor.close()
        connection.close()
    
    return render_template_string(response)

if __name__ == '__main__':
    app.run(host='192.168.52.1', port=5000, debug=True)