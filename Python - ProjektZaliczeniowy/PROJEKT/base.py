from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

engine = create_engine('postgresql://student24:st2021$24@212.182.24.105:15432/student24')
Session = sessionmaker(bind=engine)
Base = declarative_base()


