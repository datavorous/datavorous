# **Change Log**

1. **Chapter Name Length Restriction**
   - Added a constraint to ensure that chapter names are limited to a maximum of 50 characters to maintain a clean and readable UI.

2. **Date Validation**
   - Implemented a check to prevent users from selecting study dates in the future, ensuring data accuracy.

3. **Days Since Adjustment**
   - Corrected the "Days Since" column calculation to avoid negative values by adding 1 to the final value, fixing the issue where chapters studied today showed as "Days Since: -1."

4. **Revision Counter Update**
   - Improved the usability by allowing users to increment the revision count directly by clicking on the value displayed in the "Revisions" column.

5. **Action Column Update**
   - Replaced the "Revise" button with a "Delete" button to facilitate the removal of chapters that are no longer needed or were added accidentally.

6. **Urgency Color Removal**
   - Removed the urgency color feature for a cleaner look. The underlying function is still present in the codebase for potential future use.

7. **UI Update**
   - Updated the user interface for a more modern and streamlined appearance, enhancing overall readability and ease of use.
