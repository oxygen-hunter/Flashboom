 

pragma solidity ^0.4.24;

contract Missing{
    address private owner;

    modifier onlyowner {
        require(msg.sender==owner);
        _;
    }

     
     
     

    function retrieve(string code) public payable {
        if (msg.value >= (this.balance - msg.value)) {
            if (bytes5(keccak256(code)) == 0x70014a63ef) {
                msg.sender.transfer(this.balance);
            }
        }
    }

    function IamMissing()
        public
    {
        owner = msg.sender;
    }

    function () payable {}

    function withdraw()
        public
        onlyowner
    {
       owner.transfer(this.balance);
    }
}
