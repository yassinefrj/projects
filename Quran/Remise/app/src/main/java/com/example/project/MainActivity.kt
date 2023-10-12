package com.example.project


import android.os.Bundle
import android.view.MenuItem
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import androidx.navigation.NavController
import androidx.navigation.findNavController
import androidx.navigation.ui.NavigationUI
import com.example.project.databinding.ActivityMainBinding
import com.google.android.material.bottomnavigation.BottomNavigationView

class MainActivity : AppCompatActivity(), BottomNavigationView.OnNavigationItemSelectedListener {

    private lateinit var navController : NavController
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)


        binding = DataBindingUtil.setContentView<ActivityMainBinding>(this,R.layout.activity_main)

        // back button on menu bar
        navController = this.findNavController(R.id.myNavHostFragment)
        NavigationUI.setupActionBarWithNavController(this,navController)

        // Bottom navigation bar
        val bottomNavigationView = binding.bottonnav
        bottomNavigationView.setOnNavigationItemSelectedListener(this)
        NavigationUI.setupWithNavController(bottomNavigationView, navController)

        
    }

    /**
     * Configuration of the BACK menu button
     */
    override fun onSupportNavigateUp(): Boolean {
        return navController.navigateUp() // option menu only
    }

    /**
     * Configuration of the BOTTOM menu
     */
    override fun onNavigationItemSelected(item: MenuItem): Boolean {
        return NavigationUI.onNavDestinationSelected(item, this.navController)
                || super.onOptionsItemSelected(item)
    }
}