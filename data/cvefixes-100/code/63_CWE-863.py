def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key