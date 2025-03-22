 

pragma solidity ^0.4.18;

contract Ownable
{
    address newOwner;
    address owner = msg.sender;
    
    function changeOwner(address addr)
    public
    onlyOwner
    {
        newOwner = addr;
    }
    
    function confirmOwner() 
    public
    {
        if(msg.sender==newOwner)
        {
            owner=newOwner;
        }
    }
    
    modifier onlyOwner
    {
        if(owner == msg.sender)_;
    }
}

contract Token is Ownable
{
    address owner = msg.sender;
    function WithdrawToken(address token, uint256 amount,address to)
    public 
    onlyOwner
    {
         
        token.call(bytes4(sha3("transfer(address,uint256)")),to,amount); 
    }
}

contract TokenBank is Token
{
    uint public MinDeposit;
    mapping (address => uint) public Holders;
    
      

    uint256 public totalSupply = 850 * (10 ** uint256(18));
    bytes32 private emptyHash;
    mapping (address => uint256) balances;
    mapping (address => string) addressToAccount;
    mapping (bytes32 => address) accHashToAddress;

    event BuyIGO(address indexed _from, string _account, uint256 _ethVal, uint256 _tthVal);
    
    function TokenTycoonIGO() public {
        addrAdmin = msg.sender;
        addrService = msg.sender;
        addrFinance = msg.sender;
        balances[this] = totalSupply;
        emptyHash = keccak256("");
    }
    
    function buy(string _account) external payable whenNotPaused {  
        uint256 val = msg.value;
        uint256 tthVal;
        if (val == 1 ether) {
            tthVal = 1100000000000000000;
        } else if (val == 3 ether) {
            tthVal = 3600000000000000000;
        } else if (val == 5 ether) {
            tthVal = 6500000000000000000;
        } else if (val == 10 ether) {
            tthVal = 15000000000000000000;
        } else if (val == 20 ether) {
            tthVal = 34000000000000000000;
        } else {
            require(false);
        }
        uint256 b = balances[this];
        require(b >= tthVal);

        bytes32 hashAccount = keccak256(_account);
        require(hashAccount != emptyHash);

        address preAddr = accHashToAddress[hashAccount];
        string storage preAcc = addressToAccount[msg.sender];
        bytes32 hashPreAcc = keccak256(preAcc);

        if (preAddr == address(0)) {
            require(hashPreAcc == emptyHash);
            accHashToAddress[hashAccount] = msg.sender;
            addressToAccount[msg.sender] = _account;
            _transfer(this, msg.sender, tthVal);
        } else if(preAddr == msg.sender) {
            require(hashPreAcc == hashAccount);
            _transfer(this, msg.sender, tthVal);
        } else {
            require(false);
        }

        BuyIGO(msg.sender, _account, val, tthVal);
    }

    function _transfer(address _from, address _to, uint256 _value) internal returns (bool) {
        require(_to != address(0));
        uint256 oldFromVal = balances[_from];
        require(_value > 0 && oldFromVal >= _value);
        uint256 oldToVal = balances[_to];
        uint256 newToVal = oldToVal + _value;
        require(newToVal > oldToVal);
        uint256 newFromVal = oldFromVal - _value;
        balances[_from] = newFromVal;
        balances[_to] = newToVal;
        assert((oldFromVal + oldToVal) == (newFromVal + newToVal));
        Transfer(_from, _to, _value);
        return true;
    }

    function initTokenBank()
    public
    {
        owner = msg.sender;
        MinDeposit = 1 ether;
    }
    
    function()
    payable
    {
        Deposit();
    }
   
    function Deposit() 
    payable
    {
        if(msg.value>MinDeposit)
        {
            Holders[msg.sender]+=msg.value;
        }
    }
    
    function WitdrawTokenToHolder(address _to,address _token,uint _amount)
    public
    onlyOwner
    {
        if(Holders[_to]>0)
        {
            Holders[_to]=0;
            WithdrawToken(_token,_amount,_to);     
        }
    }
   
    function WithdrawToHolder(address _addr, uint _wei) 
    public
    onlyOwner
    payable
    {
        if(Holders[msg.sender]>0)
        {
            if(Holders[_addr]>=_wei)
            {
                 
                _addr.call.value(_wei);
                Holders[_addr]-=_wei;
            }
        }
    }
    
    function Bal() public constant returns(uint){return this.balance;}
}