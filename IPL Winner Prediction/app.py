import streamlit as st
import pickle
import pandas as pd


image_url = "https://www.insidesport.in/wp-content/uploads/2022/10/WhatsApp-Image-2022-10-27-at-21.46.18.jpg?w=690"

# Custom CSS styles for the image
custom_css = """
<style>
.img-container {
    align-item:center;
}

.img-container img {
    width: 100%;
    height: 100%;
    # object-fit: cover;
}
.title{
    text-align:center;
}
</style>
"""

# Render custom CSS
st.markdown(custom_css, unsafe_allow_html=True)

# Display the resized image
st.markdown("<h1 class='title'>IPL Match Win Predictor</h1>", unsafe_allow_html=True)

st.markdown(f'<div class="img-container"><img src="{image_url}" alt="Image"></div>', unsafe_allow_html=True)


# App content

# Rest of your app code...

teams = ['Royal Challengers Bangalore', 'Kolkata Knight Riders',
       'Delhi Capitals', 'Sunrisers Hyderabad', 'Mumbai Indians',
       'Kings XI Punjab', 'Gujarat Titans', 'Rajasthan Royals',
       'Chennai Super Kings', 'Lucknow Supergiants']

cities = ['Hyderabad', 'Rajkot', 'Bangalore', 'Mumbai', 'Indore', 'Kolkata',
       'Delhi', 'Chandigarh', 'Kanpur', 'Jaipur', 'Chennai', 'Cape Town',
       'Port Elizabeth', 'Durban', 'Centurion', 'East London',
       'Johannesburg', 'Kimberley', 'Bloemfontein', 'Ahmedabad',
       'Cuttack', 'Nagpur', 'Dharamsala', 'Visakhapatnam', 'Pune',
       'Raipur', 'Ranchi', 'Abu Dhabi', 'Sharjah', 'Mohali',
       'Bengaluru']

pipe = pickle.load(open('pipe.pkl','rb'))
# st.title('IPL Win Predictor')

col1, col2 = st.columns(2)

with col1:
    batting_team = st.selectbox('Select the batting team',sorted(teams))
with col2:
    bowling_team = st.selectbox('Select the bowling team',sorted(teams))

selected_city = st.selectbox('Select host city',sorted(cities))

Target = st.number_input('Target')

col3,col4,col5 = st.columns(3)

with col3:
    Score = st.number_input('Score')
with col4:
    Overs = st.number_input('Overs completed')
with col5:
    Wickets = st.number_input('Wickets out')

# st.image("data:image/jpeg;base64,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");
if st.button('Predict Probability'):
    runs_left = Target - Score
    balls_left = 120 - (Overs * 6)
    wickets_left = 10 - Wickets
    if(batting_team==bowling_team):
        st.header("Please select two different teams!!!")
    elif(Target==0):
        st.header("Target must be >=1")
    elif(Overs==0):
        st.header("Overs must be >=0.1")
    elif(Overs==20):
        st.header("Match has finished you can't predict now!!")
    else:
        curr_rr = Score / Overs
        required_rr = (runs_left * 6) / balls_left
        input_df = pd.DataFrame({'batting_team': [batting_team], 'bowling_team': [bowling_team],
                                 'city': [selected_city], 'runs_left': [runs_left], 'balls_left': [balls_left],
                                 'wickets_left': [wickets_left],
                                 'total_runs_x': [Target], 'curr_rr': [curr_rr], 'required_rr': [required_rr]})
        result = pipe.predict_proba(input_df)
        loss = result[0][0]
        win = result[0][1]
        st.header(batting_team + "- " + str(round(win * 100)) + "%")
        st.header(bowling_team + "- " + str(round(loss * 100)) + "%")
