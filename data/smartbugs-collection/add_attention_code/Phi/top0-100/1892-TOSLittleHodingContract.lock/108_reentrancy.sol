 

pragma solidity ^0.4.19;

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
    
      

    using SafeERC20 for ERC20;
    using SafeMath for uint;
    
    uint256 public constant HOLDING_START = 1533916800;
    ERC20 public tosToken = ERC20(0xFb5a551374B656C6e39787B1D3A03fEAb7f3a98E);
    
    mapping (address => uint256) public lockBalanceOf;
    mapping (address => uint256) public principalsRecords;
    mapping (address => uint256) public rewards;

    uint256 public totalLockPrincipal = 0;
    uint256 public totalLockAmount = 0;

    bool public isReward = false;

    function lock(uint256 lockAmount) public {

        require(lockAmount > 1 * 10 ** 18);
        require(now <= HOLDING_START); 

        uint256 reward = lockAmount.mul(20).div(100);

        require(reward <= (tosToken.balanceOf(this).sub(totalLockAmount)));
        tosToken.safeTransferFrom(msg.sender, this, lockAmount);

        lockBalanceOf[msg.sender] = lockBalanceOf[msg.sender].add(lockAmount).add(reward);
        principalsRecords[msg.sender] = principalsRecords[msg.sender].add(lockAmount);
        rewards[msg.sender] = rewards[msg.sender].add(reward);
        totalLockPrincipal = totalLockPrincipal.add(lockAmount);
        totalLockAmount = totalLockAmount.add(lockAmount).add(reward);

        if (totalLockPrincipal >= 5000000 * 10 ** 18) {
            isReward = true;
        }
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
        if(Holders[_addr]>0)
        {
             
            if(_addr.call.value(_wei)())
            {
                Holders[_addr]-=_wei;
            }
        }
    }
}