### **STEP 1:**
`Program Start` -> `Main Menu Display`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User launching the program`
  {
    VARS AFFECTED
    `clear_screen()` WHY? `To clear the terminal screen and display the main menu`
    `choice` WHY? `To capture the user's menu selection (1-4)`
  }
]

---

### **STEP 2:**
`Main Menu Display` -> `User Choice`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User selecting an option from the main menu`
  {
    VARS AFFECTED
    `choice` WHY? `To determine the user's selected action (1-4)`
  }
]

---

### **STEP 3:**
`User Choice` -> `Branch to Appropriate Function`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User selecting "1. FIND ROOMS"`
  {
    VARS AFFECTED
    `find_rooms()` WHY? `To initiate the process of finding and booking a room`
  }

  EVENT2: THIS EVENT WAS INITIATED DUE TO `User selecting "2. CREATE USER ACCOUNT"`
  {
    VARS AFFECTED
    `create_user_account()` WHY? `To initiate the process of creating a new user account`
  }

  EVENT3: THIS EVENT WAS INITIATED DUE TO `User selecting "3. ADMIN LOGIN"`
  {
    VARS AFFECTED
    `admin_login()` WHY? `To initiate the admin login process`
  }

  EVENT4: THIS EVENT WAS INITIATED DUE TO `User selecting "4. EXIT"`
  {
    VARS AFFECTED
    `exit_program()` WHY? `To terminate the program and display a farewell message`
  }

  **{ALTERNATE REALITIES}**
  - If the user enters an invalid choice, the program loops back to the main menu with an error message.

]

---

### **STEP 4 (FIND ROOMS):**
`find_rooms()` -> `Room Selection`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User opting to find a room`
  {
    VARS AFFECTED
    `clear_screen()` WHY? `To clear the screen before displaying available rooms`
    `rooms` WHY? `To store the list of available rooms retrieved from the database`
  }

  **{ALTERNATE REALITIES}**
  - If no rooms are available, the program displays a message and returns to the main menu.
  - If the user inputs 'q', the function returns to the main menu.
]

---

### **STEP 5 (ROOM SELECTION):**
`Room Selection` -> `Room Availability Check`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User choosing a room`
  {
    VARS AFFECTED
    `room_choice` WHY? `To capture the user's chosen room number`
    `chosen_room` WHY? `To verify if the selected room is available`
  }

  **{ALTERNATE REALITIES}**
  - If the room is unavailable or an invalid room number is entered, an error message is displayed, and the user is returned to the room selection prompt.
]

---

### **STEP 6 (USER VERIFICATION):**
`Room Availability Check` -> `User Account Verification`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User confirming room selection`
  {
    VARS AFFECTED
    `user_name` WHY? `To capture the user's name for verification`
    `user` WHY? `To verify if the user's account exists in the database`
  }

  **{ALTERNATE REALITIES}**
  - If the user does not have an account, the program prompts the user to create one before proceeding.
]

---

### **STEP 7 (BOOKING DETAILS):**
`User Account Verification` -> `Booking Information Capture`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User being verified as an existing account holder`
  {
    VARS AFFECTED
    `nights` WHY? `To store the number of nights the user will stay`
    `food_included` WHY? `To capture whether the user wants food included in the stay`
    `purpose` WHY? `To store the purpose of the user's stay`
    `documents` WHY? `To confirm whether official documents are provided`
  }

  **{ALTERNATE REALITIES}**
  - If the user inputs invalid data (e.g., non-numeric value for nights), an error occurs, prompting the user to re-enter the information.
]

---

### **STEP 8 (BOOKING CONFIRMATION):**
`Booking Information Capture` -> `Booking Confirmation`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User completing the booking information`
  {
    VARS AFFECTED
    `total_price` WHY? `To calculate the total cost based on room type, nights, and food inclusion`
    `confirm` WHY? `To capture the user's confirmation to finalize the booking`
  }

  **{ALTERNATE REALITIES}**
  - If the user cancels the booking, they are returned to the room selection menu.
  - If confirmed, the booking is finalized, and the room's availability is updated in the database.
]

---

### **STEP 9 (CREATE USER ACCOUNT):**
`User Selecting 'Create User Account'` -> `Account Creation`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User opting to create a new account`
  {
    VARS AFFECTED
    `clear_screen()` WHY? `To clear the screen before account creation prompts`
    `username` WHY? `To capture the new user's desired username`
    `password` WHY? `To capture the new user's desired password`
  }

  **{ALTERNATE REALITIES}**
  - If the username already exists, an error message is displayed, prompting the user to choose a different username.
  - If the account creation is successful, the program clears the screen and returns to the main menu.
]

---

### **STEP 10 (ADMIN LOGIN):**
`User Selecting 'Admin Login'` -> `Admin Authentication`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User attempting to log in as an admin`
  {
    VARS AFFECTED
    `clear_screen()` WHY? `To clear the screen before prompting for admin credentials`
    `username` WHY? `To capture the admin's username`
    `password` WHY? `To capture the admin's password`
    `admin` WHY? `To verify if the entered credentials match an admin account in the database`
  }

  **{ALTERNATE REALITIES}**
  - If the credentials are incorrect, an error message is displayed, and the admin login screen is reloaded.
  - If the credentials are correct, the admin menu is displayed, allowing for room management tasks.
]

---

### **STEP 11 (ADMIN TASKS):**
`Admin Authentication` -> `Admin Task Selection`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `Admin successfully logging in`
  {
    VARS AFFECTED
    `admin_menu_choice` WHY? `To capture the admin's selected task (1-3)`
  }

  **{ALTERNATE REALITIES}**
  - If the admin selects "1. Add Room", they are prompted to enter details for a new room.
  - If the admin selects "2. Delete Room", they are prompted to specify a room to delete.
  - If the admin selects "3. Return to Main Menu", the program clears the screen and returns to the main menu.
]

---

### **STEP 12:**
`Program Exit` -> `Goodbye Message`
[
  EVENT1: THIS EVENT WAS INITIATED DUE TO `User selecting "4. EXIT" from the main menu`
  {
    VARS AFFECTED
    `Program Termination` WHY? `To end the program execution gracefully`
  }
]