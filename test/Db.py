import pickle


class Db:
    """Small wrapup around pickle module. Not very useful, but does its job"""
    def __init__(self, dbname='db.pcl'):
        self.dbname = dbname
        self.pcl = dict()
        try:
            with open(self.dbname, 'rb') as f:
                self.pcl = pickle.load(f)
        except FileNotFoundError:
            pass

    def add_record(self, k, v):
        """Add or update record"""
        self.pcl[k] = v

    def get(self, k):
        return self.pcl[k] if k in self.pcl.keys() else None

    def wrap_up(self):
        with open(self.dbname, 'wb') as f:
            pickle.dump(self.pcl, f)

    def __repr__(self):
        return "\n".join([str((k, v)) for k, v in list(self.pcl.items())])
