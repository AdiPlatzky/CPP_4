# קונטיינר ואיטרטורים גנריים - MyContainer 

פרויקט זה מממש קונטיינר גנרי (מבנה נתונים כללי) בשפת ++C,
התומך באחסון, הוספה ומחיקה של כל סוגי האיברים הניתנים להשוואה (`comparable`) –
לדוג' int, double, string ועוד.

## תכונות עיקריות
- מימוש מלא של מחלקה גנרית `MyContainer` עם פונקציות:
    - הוספת איבר  - `addElement`
    - מחיקת כל ההופעות של איבר (כולל זריקת חריגה במידה ולא קיים) - `removeElement` 
    - גודל הקונטיינר  - `size` 
    - אופרטור הדפסה << לתצוגה נוחה
- מימוש שישה איטרטורים ייחודיים:
    - (סדר הכנסת האיברים) - **Order**
    - (סדר עולה) - **AscendingOrder**
    - (סדר יורד) - **DescendingOrder**
    - (קצה־קצה) - **SideCrossOrder**
    - (הפוך) - **ReverseOrder**
    - (מהאמצע החוצה) - **MiddleOutOrder**
- תמיכה מלאה בטמפלטים – ניתן ליצור קונטיינר לכל סוג בר־השוואה.
- בדיקות אוטומטיות (doctest) מקיפות.

## קומפילציה והרצה

1. פתח מסוף בספריית הפרויקט.
2. הרץ את הפקודות הבאות:

```bash
make clean       # ניקוי קבצים זמניים
make             # קומפילציה
make main        # הדגמה של ריצות אלגוריתמים עם הדפסות למסך
make test        # הרצת בדיקות יחידה
make valgrind    # בדיקת זליגות זיכרון
```
כל הבדיקות נכתבו באמצעות `doctest` וניתנות להרצה ע"י `make test`.

##  מחברת

עדי פלצקי  
מספר ת.ז: 207859919  
תואר ראשון במדעי המחשב
