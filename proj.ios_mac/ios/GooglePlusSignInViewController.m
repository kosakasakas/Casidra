//
//  GooglePlusSignInViewController.m
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/05/26.
//
//

#import "GooglePlusSignInViewController.h"

#import "GTLPlusConstants.h"
#import "GPPSignInButton.h"

@interface GooglePlusSignInViewController ()

@end


@implementation GooglePlusSignInViewController

static NSString * const kClientID =
@"599142753009.apps.googleusercontent.com";

@synthesize signInButton;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    GPPSignIn *signIn = [GPPSignIn sharedInstance];
    signIn.clientID = kClientID;
    signIn.scopes = [NSArray arrayWithObjects:
                     kGTLAuthScopePlusLogin, // GTLPlusConstants.h 内で定義済み
                     nil];
    signIn.delegate = self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)finishedWithAuth: (GTMOAuth2Authentication *)auth
                   error: (NSError *) error
{
    NSLog(@"Received error %@ and auth object %@",error, auth);
}

@end
